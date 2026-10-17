"""Index candidate state-field accesses using decoded AArch64 operands."""
import bisect
import hashlib
import json

from capstone import CS_ARCH_ARM64, CS_MODE_ARM, Cs
from capstone.arm64 import ARM64_OP_IMM, ARM64_OP_MEM
from elftools.elf.elffile import ELFFile

from bounded_arm64 import ROOT


def main():
    metadata = json.loads((ROOT / 'evidence/elf_inventory.json').read_text())
    fdes = sorted(metadata['fdes'], key=lambda item: item['start'])
    starts = [item['start'] for item in fdes]
    targets = {216, 218, 219}
    decoder = Cs(CS_ARCH_ARM64, CS_MODE_ARM)
    decoder.detail = True
    decoder.skipdata = True
    context_decoder = Cs(CS_ARCH_ARM64, CS_MODE_ARM)
    context_decoder.skipdata = True
    matches = []
    chunks = []
    sample = ROOT.parent / 'libprism-sun.so'
    with sample.open('rb') as source:
        elf = ELFFile(source)
        section = elf.get_section_by_name('.text')
        text = section.data()
        base = section['sh_addr']
        for offset in range(0, len(text), 0x10000):
            data = text[offset:offset + 0x10000]
            instruction_count = 0
            for instruction in decoder.disasm(data, base + offset):
                instruction_count += 1
                if not instruction.id:
                    continue
                fields = []
                for operand in instruction.operands:
                    if operand.type == ARM64_OP_MEM and operand.mem.disp in targets:
                        fields.append({'kind': 'memory_displacement', 'offset': operand.mem.disp,
                                       'base_register': instruction.reg_name(operand.mem.base)})
                    elif operand.type == ARM64_OP_IMM and operand.imm in targets:
                        fields.append({'kind': 'immediate', 'offset': operand.imm})
                if not fields:
                    continue
                index = bisect.bisect_right(starts, instruction.address) - 1
                fde = fdes[index] if index >= 0 and instruction.address < fdes[index]['end'] else None
                position = instruction.address - base
                context_start = max(0, position - 24)
                context = [{'address': hex(item.address), 'instruction': f'{item.mnemonic} {item.op_str}'}
                           for item in context_decoder.disasm(text[context_start:position + 32], base + context_start)]
                matches.append({'address': hex(instruction.address),
                                'instruction': f'{instruction.mnemonic} {instruction.op_str}',
                                'fields': fields, 'fde': fde, 'context': context})
            chunks.append({'start': hex(base + offset), 'size': len(data), 'records': instruction_count})
            if len(chunks) % 8 == 0:
                print(f'Decoded {len(chunks)} text chunks; {len(matches)} offset candidates', flush=True)
    known = {'0x66e8e8', '0x66e920', '0x66e964', '0x68cc78'}
    observed = {match['address'] for match in matches}
    result = {'scope': 'Decoded immediate/displacement candidates, not proof of a shared state base',
              'sample_sha256': hashlib.sha256(sample.read_bytes()).hexdigest(),
              'targets_decimal': sorted(targets), 'chunks': chunks, 'matches': matches,
              'known_consumer_candidates': sorted(known), 'known_candidates_found': sorted(known & observed),
              'candidate_count': len(matches)}
    (ROOT / 'evidence/state_offset_candidates.json').write_text(json.dumps(result, indent=2))
    print(json.dumps({'text_chunks': len(chunks), 'candidate_count': len(matches),
                      'addresses': [match['address'] for match in matches]}), flush=True)


if __name__ == '__main__':
    main()
