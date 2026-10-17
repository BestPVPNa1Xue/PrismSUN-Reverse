"""Inert bounded execution of only the accessibility-list hash path.

Original ELF instructions implement sorting, CRC32 selection, update, final and
result extraction. Explicitly modeled boundaries are libc memory primitives,
the thread-local storage allocator and destructor registration. No target or OS
process is launched. Unknown imports and syscalls remain blocked.
"""
import json
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT.parent / "scripts"))
from bounded_arm64 import Arm64Fixture, DATA, SENTINEL, REGISTERS
from elftools.elf.elffile import ELFFile
from unicorn.arm64_const import UC_ARM64_REG_X0, UC_ARM64_REG_X1, UC_ARM64_REG_X2, UC_ARM64_REG_X3, UC_ARM64_REG_X8


class HashFixture(Arm64Fixture):
    def __init__(self):
        super().__init__()
        self.uc.mem_map(0x33000000, 0x200000)
        with (ROOT.parents[1] / "libprism-sun.so").open("rb") as stream:
            elf = ELFFile(stream)
            plt = elf.get_section_by_name(".plt")
            reloc = elf.get_section_by_name(".rela.plt")
            syms = elf.get_section(reloc["sh_link"])
            self.imports = {plt["sh_addr"] + 32 + 16 * i: syms.get_symbol(r["r_info_sym"]).name
                            for i, r in enumerate(reloc.iter_relocations())}
            by_name = {name: address for address, name in self.imports.items()}
            # The shared fixture handles RELATIVE relocations. Resolve the
            # absolute/GLOB_DAT entries needed for indirect libc calls too.
            for section in elf.iter_sections():
                if section["sh_type"] != "SHT_RELA":
                    continue
                symbols = elf.get_section(section["sh_link"])
                for r in section.iter_relocations():
                    if r["r_info_type"] not in (257, 1025):
                        continue
                    symbol = symbols.get_symbol(r["r_info_sym"])
                    value = symbol["st_value"] or by_name.get(symbol.name, 0)
                    if value:
                        self.uc.mem_write(r["r_offset"], struct.pack("<Q", value + r["r_addend"]))
            self.image = bytes(self.uc.mem_read(0, 0x800000))
        self.modeled = set()
        self.updates = []
        self.vtable = None
        self.handlers[0x785874] = self.tls_address
        self.handlers[0x784fd4] = lambda f: f.return_value(0)
        supported = {"malloc", "calloc", "realloc", "free", "memset", "memcpy", "memmove",
                     "__memcpy_chk", "__memmove_chk", "strlen", "memcmp", "strcmp", "memchr"}
        for address, name in self.imports.items():
            if name in supported:
                self.handlers[address] = lambda f, n=name: f.libc(n)

    def _hook(self, uc, address, size, user_data):
        if address in (0x10a218, 0x11a3bc):
            obj = uc.reg_read(UC_ARM64_REG_X0)
            table = struct.unpack("<Q", uc.mem_read(obj, 8))[0]
            self.vtable = {"address": hex(table), "slots": [hex(x) for x in struct.unpack("<QQQQQ", uc.mem_read(table, 40))]}
        if address == 0x10a218:
            data = uc.reg_read(UC_ARM64_REG_X1)
            length = uc.reg_read(UC_ARM64_REG_X2)
            self.updates.append(bytes(uc.mem_read(data, length)).hex() if length else "")
        super()._hook(uc, address, size, user_data)

    def reset(self):
        super().reset()
        self.next = 0x33000000
        self.allocations = {}
        self.tls = {}
        self.modeled = set()
        self.updates = []
        self.vtable = None

    def allocate(self, size):
        size = max(size, 1)
        address = self.next
        self.next += (size + 15) & ~15
        assert self.next < 0x33200000, "bounded arena exhausted"
        self.uc.mem_write(address, bytes(size))
        self.allocations[address] = size
        return address

    def cstring(self, address):
        result = bytearray()
        while len(result) < 131072:
            value = self.uc.mem_read(address + len(result), 1)[0]
            if not value:
                return bytes(result)
            result.append(value)
        raise ValueError("unterminated fixture C string")

    def tls_address(self, _):
        descriptor = self.uc.reg_read(UC_ARM64_REG_X0)
        if descriptor not in self.tls:
            size, _, _, initial = struct.unpack("<QQQQ", self.uc.mem_read(descriptor, 32))
            address = self.allocate(size)
            if initial:
                self.uc.mem_write(address, bytes(self.uc.mem_read(initial, size)))
            self.tls[descriptor] = address
        self.modeled.add("compiler_emutls_get_address")
        self.return_value(self.tls[descriptor])

    def libc(self, name):
        self.modeled.add(name)
        a, b, c, d = [self.uc.reg_read(r) for r in REGISTERS[:4]]
        result = a
        if name == "malloc":
            result = self.allocate(a)
        elif name == "calloc":
            result = self.allocate(a * b)
        elif name == "realloc":
            result = self.allocate(b)
            if a:
                self.uc.mem_write(result, bytes(self.uc.mem_read(a, min(b, self.allocations[a]))))
        elif name == "free":
            result = 0
        elif name in {"memcpy", "memmove", "__memcpy_chk", "__memmove_chk"}:
            if name.endswith("_chk"):
                assert c <= d
            if c:
                self.uc.mem_write(a, bytes(self.uc.mem_read(b, c)))
        elif name == "memset":
            if c:
                self.uc.mem_write(a, bytes([b & 255]) * c)
        elif name == "strlen":
            result = len(self.cstring(a))
        elif name in {"memcmp", "strcmp"}:
            left, right = ((bytes(self.uc.mem_read(a, c)), bytes(self.uc.mem_read(b, c)))
                           if name == "memcmp" else (self.cstring(a), self.cstring(b)))
            result = (left > right) - (left < right)
        elif name == "memchr":
            offset = bytes(self.uc.mem_read(a, c)).find(bytes([b & 255]))
            result = 0 if offset == -1 else a + offset
        self.return_value(result)

    def hash(self, names):
        self.reset()
        array = self.allocate(24 * len(names))
        for index, name in enumerate(names):
            # libc++ ABI v1, short or long std::string; byte lengths retained.
            if len(name) <= 22:
                representation = bytes([2 * len(name)]) + name + bytes(23 - len(name))
            else:
                address = self.allocate(len(name) + 1)
                self.uc.mem_write(address, name + b"\0")
                representation = struct.pack("<QQQ", (len(name) + 16) | 1, len(name), address)
            self.uc.mem_write(array + 24 * index, representation)
        self.uc.mem_write(DATA, struct.pack("<QQQ", array, array + 24 * len(names), array + 24 * len(names)))
        result = self.run(0x6d4374, [DATA], count=2_000_000, timeout_us=45_000_000)
        result["modeled_boundaries"] = sorted(self.modeled | {"thread_destructor_registration"})
        result["input_hex"] = [name.hex() for name in names]
        result["sorted_hex"] = []
        for index in range(len(names)):
            obj = bytes(self.uc.mem_read(array + index * 24, 24))
            if obj[0] & 1:
                _, size, address = struct.unpack("<QQQ", obj)
                value = bytes(self.uc.mem_read(address, size))
            else:
                value = obj[1:1 + obj[0] // 2]
            result["sorted_hex"].append(value.hex())
        result["algorithm"] = None
        if 0x7afb78 in self.tls:
            result["algorithm"] = self.cstring(self.tls[0x7afb78]).decode("ascii", "replace")
        result["update_chunks_hex"] = self.updates
        result["crc_vtable"] = self.vtable
        return result


if __name__ == "__main__":
    fixture = HashFixture()
    print(json.dumps(fixture.hash([value.encode() for value in sys.argv[1:]]), indent=2))
