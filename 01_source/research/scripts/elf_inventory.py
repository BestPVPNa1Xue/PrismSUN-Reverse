from pathlib import Path
import json, hashlib, struct
from elftools.elf.elffile import ELFFile
from elftools.dwarf.callframe import FDE

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT.parent / 'libprism-sun.so'
with SOURCE.open('rb') as f:
    elf = ELFFile(f)
    symbols = [{**dict(s.entry), 'name': s.name} for s in elf.get_section_by_name('.dynsym').iter_symbols()]
    fdes = []
    for ent in elf.get_dwarf_info().EH_CFI_entries():
        if isinstance(ent, FDE):
            a, n = ent['initial_location'], ent['address_range']
            fdes.append({'start': a, 'end': a+n, 'size': n})
    sections = [{**dict(s.header), 'name': s.name} for s in elf.iter_sections()]
    relocs = []
    for sec in elf.iter_sections():
        if sec.header['sh_type'] == 'SHT_RELA':
            for rel in sec.iter_relocations():
                relocs.append(dict(rel.entry))
    dynamic = []
    for tag in elf.get_section_by_name('.dynamic').iter_tags():
        row = dict(tag.entry)
        for attr in ('needed', 'soname'):
            if hasattr(tag, attr): row[attr] = getattr(tag, attr)
        dynamic.append(row)
    init = elf.get_section_by_name('.init_array')
    init_entries = list(struct.unpack('<'+'Q'*(init.data_size//8), init.data()))
    relocmap = {r['r_offset']:r for r in relocs}
    for i in range(len(init_entries)):
        r = relocmap.get(init['sh_addr']+i*8)
        if r and r['r_info_type'] == 1027: init_entries[i] = r['r_addend']
    info = {'sha256': hashlib.sha256(SOURCE.read_bytes()).hexdigest(), 'size': SOURCE.stat().st_size,
            'header': dict(elf.header), 'sections': sections, 'symbols': symbols,
            'fde_count': len(fdes), 'fdes': fdes, 'relocations': relocs,
            'dynamic': dynamic, 'initializers': init_entries}
    info = json.loads(json.dumps(info,default=lambda o:dict(o)))
    (ROOT/'evidence/elf_inventory.json').write_text(json.dumps(info,indent=2),encoding='utf-8')
    print(json.dumps({'header':info['header'],'exports':[s for s in info['symbols'] if s['st_shndx']!='SHN_UNDEF' and s['name']],
                      'fde_count': len(fdes), 'initializers':[hex(a) for a in init_entries]},indent=2))
