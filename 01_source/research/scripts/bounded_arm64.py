"""Run original instructions in an inert, bounded Unicorn memory fixture."""
import json
import struct
from pathlib import Path

from elftools.elf.elffile import ELFFile
from unicorn import Uc, UcError, UC_ARCH_ARM64, UC_MODE_ARM, UC_HOOK_CODE
from unicorn.arm64_const import (
    UC_ARM64_REG_X0, UC_ARM64_REG_X1, UC_ARM64_REG_X2, UC_ARM64_REG_X3,
    UC_ARM64_REG_X4, UC_ARM64_REG_X5, UC_ARM64_REG_X6, UC_ARM64_REG_X7,
    UC_ARM64_REG_X8, UC_ARM64_REG_X9, UC_ARM64_REG_X10, UC_ARM64_REG_X11,
    UC_ARM64_REG_X12, UC_ARM64_REG_X13, UC_ARM64_REG_X14, UC_ARM64_REG_X15,
    UC_ARM64_REG_X16, UC_ARM64_REG_X17, UC_ARM64_REG_X18, UC_ARM64_REG_X19,
    UC_ARM64_REG_X20, UC_ARM64_REG_X21, UC_ARM64_REG_X22, UC_ARM64_REG_X23,
    UC_ARM64_REG_X24, UC_ARM64_REG_X25, UC_ARM64_REG_X26, UC_ARM64_REG_X27,
    UC_ARM64_REG_X28, UC_ARM64_REG_X29, UC_ARM64_REG_X30, UC_ARM64_REG_SP,
    UC_ARM64_REG_PC, UC_ARM64_REG_TPIDR_EL0, UC_ARM64_REG_CPACR_EL1,
    UC_ARM64_REG_NZCV,
)

ROOT = Path(__file__).resolve().parents[1]
REGISTERS = [
    UC_ARM64_REG_X0, UC_ARM64_REG_X1, UC_ARM64_REG_X2, UC_ARM64_REG_X3,
    UC_ARM64_REG_X4, UC_ARM64_REG_X5, UC_ARM64_REG_X6, UC_ARM64_REG_X7,
    UC_ARM64_REG_X8, UC_ARM64_REG_X9, UC_ARM64_REG_X10, UC_ARM64_REG_X11,
    UC_ARM64_REG_X12, UC_ARM64_REG_X13, UC_ARM64_REG_X14, UC_ARM64_REG_X15,
    UC_ARM64_REG_X16, UC_ARM64_REG_X17, UC_ARM64_REG_X18, UC_ARM64_REG_X19,
    UC_ARM64_REG_X20, UC_ARM64_REG_X21, UC_ARM64_REG_X22, UC_ARM64_REG_X23,
    UC_ARM64_REG_X24, UC_ARM64_REG_X25, UC_ARM64_REG_X26, UC_ARM64_REG_X27,
    UC_ARM64_REG_X28, UC_ARM64_REG_X29, UC_ARM64_REG_X30,
]
DATA = 0x31000000
OUTPUT = DATA + 0x10000
SENTINEL = 0x32000000


class Arm64Fixture:
    def __init__(self):
        self.uc = Uc(UC_ARCH_ARM64, UC_MODE_ARM)
        self.uc.mem_map(0, 0x800000)
        with (ROOT.parent / 'libprism-sun.so').open('rb') as source:
            elf = ELFFile(source)
            self.executable = []
            self.plt = []
            for segment in elf.iter_segments():
                if segment['p_type'] == 'PT_LOAD':
                    self.uc.mem_write(segment['p_vaddr'], segment.data())
                    if segment['p_flags'] & 1:
                        self.executable.append((segment['p_vaddr'],
                                                segment['p_vaddr'] + segment['p_memsz']))
            for section in elf.iter_sections():
                if section.name.startswith('.plt'):
                    self.plt.append((section['sh_addr'],
                                     section['sh_addr'] + section['sh_size']))
        meta = json.loads((ROOT / 'evidence/elf_inventory.json').read_text())
        for relocation in meta['relocations']:
            if relocation['r_info_type'] == 1027:
                self.uc.mem_write(relocation['r_offset'],
                                  struct.pack('<Q', relocation['r_addend']))
        self.image = bytes(self.uc.mem_read(0, 0x800000))
        for address, size in [(0x20000000, 0x200000), (0x30000000, 0x10000),
                              (DATA, 0x20000), (SENTINEL, 0x1000)]:
            self.uc.mem_map(address, size)
        self.uc.reg_write(UC_ARM64_REG_CPACR_EL1, 3 << 20)
        self.uc.hook_add(UC_HOOK_CODE, self._hook)
        self.handlers = {}
        self.visited = set()

    def reset(self):
        self.uc.mem_write(0, self.image)
        self.uc.mem_write(0x201f0000, bytes(0x10000))
        self.uc.mem_write(DATA, bytes(0x20000))
        for register in REGISTERS:
            self.uc.reg_write(register, 0)
        self.uc.reg_write(UC_ARM64_REG_SP, 0x201ff000)
        self.uc.reg_write(UC_ARM64_REG_TPIDR_EL0, 0x30000000)
        self.uc.reg_write(UC_ARM64_REG_NZCV, 0)
        self.uc.reg_write(UC_ARM64_REG_X30, SENTINEL)
        self.steps = 0
        self.reason = 'instruction_or_time_budget'
        self.visited = set()
        self.calls = []

    def return_value(self, value):
        self.uc.reg_write(UC_ARM64_REG_X0, value & ((1 << 64) - 1))
        self.uc.reg_write(UC_ARM64_REG_PC, self.uc.reg_read(UC_ARM64_REG_X30))

    def _hook(self, uc, address, size, user_data):
        self.steps += 1
        self.visited.add(address)
        if address == SENTINEL:
            self.reason = 'returned'
            uc.emu_stop()
            return
        if address in self.handlers:
            self.calls.append(hex(address))
            self.handlers[address](self)
            return
        if any(low <= address < high for low, high in self.plt):
            self.reason = f'blocked_import:{address:#x}'
            uc.emu_stop()
            return
        if not any(low <= address < high for low, high in self.executable):
            self.reason = f'blocked_execution:{address:#x}'
            uc.emu_stop()
            return
        word = struct.unpack('<I', uc.mem_read(address, 4))[0]
        if word & 0xffe0001f == 0xd4000001:
            self.reason = f'blocked_syscall:{address:#x}'
            uc.emu_stop()

    def run(self, entry, args, count=500000, timeout_us=2_000_000):
        for register, value in zip(REGISTERS, args):
            self.uc.reg_write(register, value)
        try:
            self.uc.emu_start(entry, SENTINEL + 4, timeout=timeout_us, count=count)
        except UcError as error:
            self.reason = f'unicorn_error:{error}'
        return {'entry': hex(entry), 'reason': self.reason, 'steps': self.steps,
                'return': self.uc.reg_read(UC_ARM64_REG_X0),
                'pc': hex(self.uc.reg_read(UC_ARM64_REG_PC)), 'calls': self.calls}
