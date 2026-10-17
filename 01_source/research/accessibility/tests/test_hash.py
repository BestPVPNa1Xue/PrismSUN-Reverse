"""Differential tests against original AArch64 instructions, not pseudocode."""
import hashlib
import argparse
import ctypes
import os
import json
import random
import sys
import zlib
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
from hash_original import HashFixture


def reference(names):
    data = b"".join(name + b"\0" for name in sorted(names))
    crc = zlib.crc32(data)
    return int.from_bytes(crc.to_bytes(4, "big"), "little"), data


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--retry-failed", action="store_true", help="Keep source-matched passing cases; rerun only previously failed cases.")
    parser.add_argument("--model-dll", type=Path, help="Compare the compiled C++ model against all retained original-instruction cases.")
    parser.add_argument("--dll-directory", type=Path, help="Windows compiler-runtime directory used by the compiled model.")
    args = parser.parse_args()
    cases = [
        ("empty_list", []),
        ("one_empty_string", [b""]),
        ("two_empty_strings", [b"", b""]),
        ("single_ascii", [b"a"]),
        ("input_order_ab", [b"a", b"b"]),
        ("input_order_ba", [b"b", b"a"]),
        ("duplicate_retained", [b"a", b"a", b"b"]),
        ("embedded_nul", [b"a\0b"]),
        ("case_and_prefix", [b"aa", b"a", b"A", b"aA", b"AA"]),
        ("unsigned_bytes", [b"\xff", b"\x80", b"\x7f", b"\x00", b"\x01"]),
        ("unicode_utf8_bytes", ["键映射器".encode(), "KeyMapper".encode(), "😀".encode()]),
        ("modified_utf8_nul_bytes", [b"a\xc0\x80b", b"a\0b"]),
        ("short_long_string_boundary", [b"z" * 23, b"z" * 22, b"a" * 24]),
        ("crc_16_byte_update_boundary", [bytes(range(n)) for n in (0, 1, 15, 16, 17, 31, 32, 33)]),
        ("long_name", [b"long.service.name." * 120]),
        ("sort_24_element_boundary", [str(i).encode() for i in reversed(range(24))]),
        ("sort_129_elements", [str(i).encode() for i in reversed(range(129))]),
        ("keymapper_label", [b"io.github.sds100.keymapper", b"TARGET.service"]),
    ]
    rng = random.Random(0x6D4374)
    for i in range(24):
        cases.append((f"random_bytes_{i:02}", [rng.randbytes(rng.randrange(0, 97)) for _ in range(rng.randrange(0, 13))]))
    fixture = HashFixture()
    results = []
    output = ROOT / "evidence" / "hash-differential.json"
    source_sha256 = hashlib.sha256((ROOT.parents[1] / "libprism-sun.so").read_bytes()).hexdigest()
    previous = {}
    if args.retry_failed:
        saved = json.loads(output.read_text(encoding="utf-8"))
        assert saved["sha256"] == source_sha256
        previous = {result["case"]: result for result in saved["cases"] if result["pass"]}
    for name, names in cases:
        if name in previous:
            result = previous[name]
            assert result["input_hex"] == [value.hex() for value in names]
            results.append(result)
            continue
        result = fixture.hash(names)
        expected, message = reference(names)
        result.update(case=name, expected=expected, message_hex=message.hex())
        result["pass"] = (result["reason"] == "returned"
                          and result["return"] == expected
                          and result["sorted_hex"] == [n.hex() for n in sorted(names)]
                          and result["algorithm"] == "CRC32"
                          and "".join(result["update_chunks_hex"]) == message.hex())
        results.append(result)
        if not result["pass"]:
            print(json.dumps(result, indent=2))
    by_name = {r["case"]: r for r in results}
    assert by_name["input_order_ab"]["return"] == by_name["input_order_ba"]["return"]
    assert by_name["input_order_ab"]["return"] == by_name["embedded_nul"]["return"]
    assert by_name["duplicate_retained"]["return"] != by_name["input_order_ab"]["return"]
    assert by_name["empty_list"]["return"] == 0
    assert by_name["one_empty_string"]["return"] != 0
    sample = ROOT.parents[1] / "libprism-sun.so"
    evidence = {
        "source": str(sample), "sha256": source_sha256,
        "entry": "0x6d4374", "oracle": "zlib.crc32(sorted NUL-terminated byte names), bswap32",
        "result": "PASS" if all(r["pass"] for r in results) else "FAIL",
        "count": len(results), "passed": sum(r["pass"] for r in results),
        "scope": "Original sorting, CRC factory, update/final, digest extraction and cleanup instructions run; listed libc/TLS boundaries are modeled.",
        "cases": results,
    }
    output.write_text(json.dumps(evidence, ensure_ascii=False, indent=2), encoding="utf-8")
    print(f'{evidence["result"]}: {evidence["passed"]}/{len(results)} original-instruction differential cases; {output}')
    if args.model_dll:
        class Bytes(ctypes.Structure):
            _fields_ = [("data", ctypes.c_void_p), ("size", ctypes.c_size_t)]
        dll_path = args.model_dll.resolve()
        dll_search = os.add_dll_directory(str(args.dll_directory.resolve())) if args.dll_directory else None
        library = ctypes.CDLL(str(dll_path))
        model = library.a11y_snapshot_hash
        model.argtypes = [ctypes.POINTER(Bytes), ctypes.c_size_t]
        model.restype = ctypes.c_uint32
        comparisons = []
        for original in results:
            values = [bytes.fromhex(value) for value in original["input_hex"]]
            buffers = [ctypes.create_string_buffer(value) for value in values]
            spans = (Bytes * len(values))(*(Bytes(ctypes.cast(buf, ctypes.c_void_p), len(value))
                                             for buf, value in zip(buffers, values)))
            actual = model(spans, len(values))
            comparisons.append({"case": original["case"], "original": original["return"],
                                "cpp": actual, "pass": original["pass"] and actual == original["return"]})
        cpp_evidence = {"source_sha256": source_sha256, "dll": str(dll_path),
                        "dll_sha256": hashlib.sha256(dll_path.read_bytes()).hexdigest(),
                        "count": len(comparisons), "passed": sum(item["pass"] for item in comparisons),
                        "cases": comparisons}
        (ROOT / "evidence" / "hash-cpp-differential.json").write_text(json.dumps(cpp_evidence, indent=2), encoding="utf-8")
        print(f'C++ differential: {cpp_evidence["passed"]}/{len(comparisons)} PASS')
        assert all(item["pass"] for item in comparisons)
    return 0 if evidence["result"] == "PASS" else 1


if __name__ == "__main__":
    raise SystemExit(main())
