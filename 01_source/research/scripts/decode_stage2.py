"""Extract XOR parameters from bounded, isolated AArch64 wrapper execution.

No imported function, OS syscall, or unknown helper is forwarded. Synthetic
objects contain one bytes so the encrypted flag is set at any valid offset.
Plaintext pairing is a candidate until a caller establishes the data flow.
"""
import bisect
import json
import struct
from pathlib import Path

from elftools.elf.elffile import ELFFile
from unicorn import Uc, UcError, UC_ARCH_ARM64, UC_MODE_ARM, UC_HOOK_CODE
from unicorn.arm64_const import (
    UC_ARM64_REG_X0, UC_ARM64_REG_X1, UC_ARM64_REG_X2, UC_ARM64_REG_X29,
    UC_ARM64_REG_X30, UC_ARM64_REG_SP, UC_ARM64_REG_TPIDR_EL0,
    UC_ARM64_REG_CPACR_EL1, UC_ARM64_REG_NZCV,
)

ROOT = Path(__file__).resolve().parents[1]
DECODER = 0x2BC7B0
OBJECT = 0x31000000
SENTINEL = 0x32000000
meta = json.loads((ROOT / 'evidence/elf_inventory.json').read_text())
u = Uc(UC_ARCH_ARM64, UC_MODE_ARM)
u.mem_map(0, 0x800000)
with (ROOT.parent / 'libprism-sun.so').open('rb') as source:
    elf = ELFFile(source)
    for segment in elf.iter_segments():
        if segment['p_type'] == 'PT_LOAD':
            u.mem_write(segment['p_vaddr'], segment.data())
for relocation in meta['relocations']:
    if relocation['r_info_type'] == 1027:
        u.mem_write(relocation['r_offset'], struct.pack('<Q', relocation['r_addend']))
for address, size in [(0x20000000, 0x200000), (0x30000000, 0x10000),
                      (OBJECT, 0x10000), (SENTINEL, 0x1000)]:
    u.mem_map(address, size)
u.reg_write(UC_ARM64_REG_CPACR_EL1, 3 << 20)
image = bytes(u.mem_read(0, 0x800000))
text_section = next(s for s in meta['sections'] if s['name'] == '.text')
low = text_section['sh_addr']
high = low + text_section['sh_size']


def branch_target(address, word):
    delta = word & 0x3ffffff
    if delta & 0x2000000:
        delta -= 0x4000000
    return address + 4 * delta


def resolves_to_decoder(address):
    seen = set()
    for _ in range(8):
        if address == DECODER:
            return True
        if address in seen or not low <= address < high:
            return False
        seen.add(address)
        word = struct.unpack_from('<I', image, address)[0]
        if word & 0xfc000000 != 0x14000000:
            return False
        address = branch_target(address, word)
    return False


ranges = sorted(meta['fdes'], key=lambda entry: entry['start'])
starts = [entry['start'] for entry in ranges]
wrappers = {}
direct_calls = []
for address in range(low, high - 3, 4):
    word = struct.unpack_from('<I', image, address)[0]
    if word & 0xfc000000 != 0x94000000:
        continue
    direct_calls.append((address, branch_target(address, word)))
    if not resolves_to_decoder(branch_target(address, word)):
        continue
    index = bisect.bisect_right(starts, address) - 1
    if index >= 0 and address < ranges[index]['end']:
        fn = ranges[index]
        wrappers.setdefault(fn['start'], fn)

inner_wrappers = set(wrappers)


def resolve_thunk(address):
    for _ in range(8):
        if not low <= address < high:
            return address
        word = struct.unpack_from('<I', image, address)[0]
        if word & 0xfc000000 != 0x14000000:
            return address
        address = branch_target(address, word)
    return address


for address, target in direct_calls:
    if resolve_thunk(target) not in inner_wrappers:
        continue
    index = bisect.bisect_right(starts, address) - 1
    if index >= 0 and address < ranges[index]['end'] and ranges[index]['size'] <= 2048:
        fn = ranges[index]
        wrappers.setdefault(fn['start'], fn)

current = None
capture = None
reason = ''
steps = 0


def on_code(uc, address, size, _):
    global capture, reason, steps
    steps += 1
    if address == DECODER:
        capture = {'wrapper': hex(current['start']), 'callsite': hex(previous[0]),
                   'length': uc.reg_read(UC_ARM64_REG_X1),
                   'key': hex(uc.reg_read(UC_ARM64_REG_X2)), 'steps': steps,
                   'synthetic_object_preserved': uc.reg_read(UC_ARM64_REG_X0) == OBJECT}
        reason = 'captured_decoder_entry'
        uc.emu_stop()
        return
    if address == SENTINEL:
        reason = 'returned_without_decode'
        uc.emu_stop()
        return
    if not low <= address < high:
        reason = 'outside_text'
        uc.emu_stop()
        return
    word = struct.unpack_from('<I', image, address)[0]
    if word & 0xfc000000 == 0x94000000:
        target = branch_target(address, word)
        if not resolves_to_decoder(target) and resolve_thunk(target) not in inner_wrappers:
            reason = 'unknown_call_at_' + hex(address)
            uc.emu_stop()
    elif word & 0xfffffc1f == 0xd63f0000:
        reason = 'indirect_call_at_' + hex(address)
        uc.emu_stop()
    elif word & 0xffe0001f == 0xd4000001:
        reason = 'syscall'
        uc.emu_stop()
    previous[0] = address


u.hook_add(UC_HOOK_CODE, on_code)
keys = []
attempts = []
previous = [0]
for index, current in enumerate(wrappers.values()):
    capture = None
    reason = 'instruction_budget'
    steps = 0
    previous[0] = 0
    u.mem_write(OBJECT, bytes([1]) * 0x10000)
    u.mem_write(0x20000000, bytes(0x200000))
    for register in [UC_ARM64_REG_X0 + i for i in range(29)] + [UC_ARM64_REG_X29]:
        u.reg_write(register, 0)
    u.reg_write(UC_ARM64_REG_X0, OBJECT)
    u.reg_write(UC_ARM64_REG_X30, SENTINEL)
    u.reg_write(UC_ARM64_REG_SP, 0x20100000)
    u.reg_write(UC_ARM64_REG_TPIDR_EL0, 0x30000000)
    u.reg_write(UC_ARM64_REG_NZCV, 0)
    try:
        u.emu_start(current['start'], SENTINEL + 4, count=50000)
    except UcError as error:
        reason = str(error)
    attempts.append({'wrapper': hex(current['start']), 'stop': reason, 'steps': steps})
    if capture and 0 < capture['length'] <= 4096:
        keys.append(capture)
    if index % 10 == 0:
        print(f'{index}/{len(wrappers)} wrappers; {len(keys)} parameter sets', flush=True)
        (ROOT / 'evidence/stage2_keys.partial.json').write_text(json.dumps(keys, indent=2))

sources = json.loads((ROOT / 'evidence/core_prefix_decode.json').read_text())
pairs = []
parameters = {}
for entry in keys:
    parameters.setdefault((entry['length'], entry['key']), []).append(entry['wrapper'])
for writer in sources:
    for chunk in writer['chunks']:
        raw = bytes.fromhex(chunk['bytes'])
        for (length, key), wrapper_addresses in parameters.items():
            if len(raw) != length:
                continue
            key_bytes = int(key, 16).to_bytes(8, 'little')
            decoded = bytes(byte ^ key_bytes[i % 8] for i, byte in enumerate(raw))
            text = decoded.rstrip(b'\x00')
            if len(text) < 3 or not all(32 <= byte <= 126 for byte in text):
                continue
            pairs.append({'writer': writer['function'], 'data': chunk['address'],
                          'length': length, 'key': key, 'wrappers': wrapper_addresses,
                          'plaintext': text.decode('ascii'), 'bytes': decoded.hex(),
                          'confidence': 'candidate_parameter_match'})
for filename, value in [('stage2_keys.json', keys), ('stage2_attempts.json', attempts),
                        ('stage2_candidates.json', pairs)]:
    (ROOT / 'evidence' / filename).write_text(json.dumps(value, indent=2), encoding='utf-8')
print(f'DONE: {len(keys)} captured wrappers; {len(pairs)} plaintext candidates', flush=True)
for entry in pairs:
    print(entry['writer'], entry['plaintext'], flush=True)
