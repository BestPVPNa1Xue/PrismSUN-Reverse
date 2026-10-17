"""Index direct calls and verify adjacent writer-to-wrapper register flow."""
import bisect
import json
import struct
from pathlib import Path
from capstone import Cs, CS_ARCH_ARM64, CS_MODE_ARM
from elftools.elf.elffile import ELFFile

ROOT = Path(__file__).resolve().parents[1]
meta = json.loads((ROOT / 'evidence/elf_inventory.json').read_text())
image = bytearray(0x800000)
with (ROOT.parent / 'libprism-sun.so').open('rb') as source:
    elf = ELFFile(source)
    for segment in elf.iter_segments():
        if segment['p_type'] == 'PT_LOAD':
            address = segment['p_vaddr']
            image[address:address + segment['p_filesz']] = segment.data()
text_section = next(s for s in meta['sections'] if s['name'] == '.text')
low, high = text_section['sh_addr'], text_section['sh_addr'] + text_section['sh_size']
ranges = sorted(meta['fdes'], key=lambda row: row['start'])
starts = [row['start'] for row in ranges]
disassembler = Cs(CS_ARCH_ARM64, CS_MODE_ARM)


def branch(address, word):
    offset = word & 0x3ffffff
    if offset & 0x2000000:
        offset -= 0x4000000
    return address + 4 * offset


def resolve(address):
    seen = set()
    for _ in range(8):
        if address in seen or not low <= address < high:
            break
        seen.add(address)
        word = struct.unpack_from('<I', image, address)[0]
        if word & 0xfc000000 != 0x14000000:
            break
        address = branch(address, word)
    return address


def enclosing(address):
    index = bisect.bisect_right(starts, address) - 1
    if index >= 0 and address < ranges[index]['end']:
        return ranges[index]
    return None


calls = {}
for address in range(low, high - 3, 4):
    word = struct.unpack_from('<I', image, address)[0]
    if word & 0xfc000000 == 0x94000000:
        calls.setdefault(resolve(branch(address, word)), []).append(address)
candidates = json.loads((ROOT / 'evidence/stage2_candidates.json').read_text())
for row in candidates:
    wrapper_targets = {int(address, 16) for address in row['wrappers']}
    row['caller_evidence'] = []
    for address in calls.get(int(row['writer'], 16), []):
        fn = enclosing(address)
        registers = {'x0'}
        proof = None
        cursor = address + 4
        for _ in range(16):
            instruction = next(disassembler.disasm(bytes(image[cursor:cursor + 4]), cursor), None)
            if instruction is None:
                break
            cursor += 4
            operands = [part.strip() for part in instruction.op_str.split(',')]
            if instruction.mnemonic == 'bl':
                word = struct.unpack_from('<I', image, instruction.address)[0]
                target = resolve(branch(instruction.address, word))
                if 'x0' in registers and target in wrapper_targets:
                    proof = {'decode_callsite': hex(instruction.address), 'wrapper': hex(target)}
                break
            if instruction.mnemonic == 'b':
                word = struct.unpack_from('<I', image, instruction.address)[0]
                cursor = branch(instruction.address, word)
                if not address < cursor < address + 68:
                    break
                continue
            if instruction.mnemonic.startswith('b') or instruction.mnemonic in ('ret', 'cbz', 'cbnz', 'tbz', 'tbnz'):
                break
            if instruction.mnemonic == 'mov' and len(operands) == 2:
                if operands[1] in registers:
                    registers.add(operands[0])
                else:
                    registers.discard(operands[0])
            elif instruction.mnemonic == 'nop':
                pass
            elif operands:
                registers.discard(operands[0])
        evidence = {'writer_callsite': hex(address),
                    'caller': hex(fn['start']) if fn else None,
                    'caller_end': hex(fn['end']) if fn else None,
                    'register_flow': proof}
        row['caller_evidence'].append(evidence)
    if any(item['register_flow'] for item in row['caller_evidence']):
        row['confidence'] = 'verified_direct_register_flow'
(ROOT / 'evidence/stage2_strings.json').write_text(json.dumps(candidates, indent=2), encoding='utf-8')
verified = sum(row['confidence'] == 'verified_direct_register_flow' for row in candidates)
print(f'{verified}/{len(candidates)} candidates linked by adjacent calls and X0 flow', flush=True)
for row in candidates:
    print(row['writer'], row['confidence'], repr(row['plaintext']),
          [item['caller'] for item in row['caller_evidence']], flush=True)
