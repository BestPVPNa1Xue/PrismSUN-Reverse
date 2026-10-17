"""Run the original accessibility consumer and helpers in bounded Unicorn.

Only singleton lookup, JNI acquisition/enumeration and diagnostic text are
fixtures. STL copy/sort, cJSON construction, CRC32, atomics and result
constructors execute the sample's instructions. Allocator/libc/TLS boundaries
are inherited from hash_original, never an Android process or network.
"""
import json
import struct
from hash_original import HashFixture, DATA
from unicorn.arm64_const import UC_ARM64_REG_X0, UC_ARM64_REG_X8

OUTPUT = DATA + 0x10000


class ConsumerFixture(HashFixture):
    def __init__(self):
        super().__init__()
        self.handlers[0x3b8c40] = lambda f: f.return_value(DATA)
        self.handlers[0x306df0] = lambda f: f.return_value(0)
        self.handlers[0x6ae7d0] = lambda f: f.return_value(int(self.env_available))
        self.handlers[0x6b0660] = lambda f: f.return_value(DATA + 0x800)
        self.handlers[0x3078cc] = lambda f: f.return_value(0)
        self.handlers[0x31b73c] = self.enumerate
        for address in [0x6d30a4, 0x6dd8b8, 0x6dd8bc, 0x74539c]:
            self.handlers[address] = lambda f: f.return_value(0)

    def enumerate(self, _):
        output = self.uc.reg_read(UC_ARM64_REG_X8)
        array = self.allocate(24 * len(self.names))
        for i, name in enumerate(self.names):
            if len(name) <= 22:
                value = bytes([2 * len(name)]) + name + bytes(23 - len(name))
            else:
                address = self.allocate(len(name) + 1)
                self.uc.mem_write(address, name + b'\0')
                value = struct.pack('<QQQ', (len(name) + 16) | 1, len(name), address)
            self.uc.mem_write(array + i * 24, value)
        end = array + 24 * len(self.names)
        self.uc.mem_write(output, struct.pack('<QQQ', array, end, end))
        self.return_value(output)

    def consume(self, names, initialized=False, previous_hash=0, env_available=True):
        self.reset()
        self.names = names
        self.env_available = env_available
        self.uc.mem_write(DATA + 552, struct.pack('<IB', previous_hash, initialized))
        self.uc.mem_write(OUTPUT, bytes([0xcc]) * 40)
        self.uc.reg_write(UC_ARM64_REG_X8, OUTPUT)
        result = self.run(0x6cf0c8, [0, 0], count=4_000_000, timeout_us=40_000_000)
        raw = bytes(self.uc.mem_read(OUTPUT, 24))
        kind = int.from_bytes(raw[:4], 'little')
        result['observation'] = {
            'kind': kind, 'event_type': raw[4],
            'error_code': int.from_bytes(raw[16:20], 'little'),
            'previous_hash': int.from_bytes(self.uc.mem_read(DATA + 552, 4), 'little'),
            'initialized': self.uc.mem_read(DATA + 556, 1)[0],
            'payload_hex': [],
            'guard_unchanged': bytes(self.uc.mem_read(OUTPUT + 24, 16)) == bytes([0xcc]) * 16,
        }
        if result['reason'] == 'returned' and kind == 0:
            node = int.from_bytes(raw[8:16], 'little')
            result['observation']['cjson_type'] = int.from_bytes(self.uc.mem_read(node + 24, 4), 'little')
            child = int.from_bytes(self.uc.mem_read(node + 16, 8), 'little')
            while child:
                assert len(result['observation']['payload_hex']) <= len(names)
                string = int.from_bytes(self.uc.mem_read(child + 32, 8), 'little')
                result['observation']['payload_hex'].append(self.cstring(string).hex())
                child = int.from_bytes(self.uc.mem_read(child, 8), 'little')
        result['input_hex'] = [n.hex() for n in names]
        result['modeled_boundaries'] = sorted(self.modeled | {
            'singleton_lookup', 'JNIEnv_acquisition_and_cleanup', 'JNI_service_ID_vector',
            'diagnostic_text', 'thread_destructor_registration'})
        return result


if __name__ == '__main__':
    fixture = ConsumerFixture()
    print(json.dumps(fixture.consume([b'z', b'a']), indent=2))
