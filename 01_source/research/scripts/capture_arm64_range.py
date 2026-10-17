"""Capture an immutable AArch64 listing for a virtual-address range."""
import argparse
import hashlib
import json
import struct
from pathlib import Path

from capstone import CS_ARCH_ARM64, CS_MODE_ARM, Cs
from elftools.elf.elffile import ELFFile


def direct_target(address, word, kind):
    if kind == "bl" and word & 0xFC000000 == 0x94000000:
        imm = word & 0x03FFFFFF
    elif kind == "b" and word & 0xFC000000 == 0x14000000:
        imm = word & 0x03FFFFFF
    else:
        return None
    if imm & 0x02000000:
        imm -= 0x04000000
    return address + (imm << 2)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--input", default="D:/PrismSUN/libprism-sun.so")
    parser.add_argument("--start", required=True, type=lambda value: int(value, 0))
    parser.add_argument("--end", required=True, type=lambda value: int(value, 0))
    parser.add_argument("--output", required=True)
    args = parser.parse_args()
    if args.end <= args.start or (args.end - args.start) % 4:
        raise SystemExit("range must be a positive instruction-aligned span")

    sample = Path(args.input)
    image = bytearray(args.end)
    with sample.open("rb") as source:
        elf = ELFFile(source)
        for segment in elf.iter_segments():
            if segment["p_type"] != "PT_LOAD":
                continue
            begin = segment["p_vaddr"]
            data = segment.data()
            image[begin:begin + len(data)] = data

    decoder = Cs(CS_ARCH_ARM64, CS_MODE_ARM)
    decoder.detail = True
    decoder.skipdata = True
    data = bytes(image[args.start:args.end])
    instructions = []
    for insn in decoder.disasm(data, args.start):
        word = struct.unpack("<I", insn.bytes.ljust(4, b"\0")) [0]
        row = {
            "address": hex(insn.address),
            "bytes": insn.bytes.hex(),
            "mnemonic": insn.mnemonic,
            "op_str": insn.op_str,
        }
        if insn.mnemonic in ("bl", "b"):
            target = direct_target(insn.address, word, insn.mnemonic)
            if target is not None:
                row["direct_target"] = hex(target)
        instructions.append(row)

    result = {
        "sample": str(sample),
        "sample_sha256": hashlib.sha256(sample.read_bytes()).hexdigest(),
        "start": hex(args.start),
        "end": hex(args.end),
        "instruction_count": len(instructions),
        "instructions": instructions,
    }
    output = Path(args.output)
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(result, indent=2), encoding="utf-8")
    print(json.dumps({"output": str(output), "instruction_count": len(instructions)}, ensure_ascii=False))


if __name__ == "__main__":
    main()
