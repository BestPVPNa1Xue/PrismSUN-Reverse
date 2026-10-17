"""Convert saved original results into C++ checks, without executing original code."""
import json
from pathlib import Path

root = Path(__file__).resolve().parents[1]
lines = ["// Replay saved original-instruction results; does not rerun original code.",
         "static void saved_vector_tests() {"]
digest = json.loads((root / "evidence/digest-differential.json").read_text())
for case in digest["cases"]:
    assert case["pass"] and case["return"] == case["expected"]
    literal = ",".join(str(b) for b in bytes.fromhex(case["data_hex"]))
    lines.append("check(crc32_bswap(std::vector<std::uint8_t>{" + literal + "})==" +
                 str(case["return"]) + 'U,"saved native digest");')
ime = json.loads((root / "evidence/ime-hash-differential.json").read_text())
for case in ime["cases"]:
    assert case["pass_result"] and case["return"] == case["expected"]
    names = []
    for value in case["input_hex"]:
        raw = bytes.fromhex(value)
        literal = "".join("\\x%02x" % b for b in raw)
        names.append('std::string("' + literal + '",' + str(len(raw)) + ')')
    lines.append("check(input_method_hash({" + ",".join(names) + "})==" +
                 str(case["return"]) + 'U,"saved native IME hash");')
lines.append("}")
(root / "tests/saved_digest_vectors.inc").write_text("\n".join(lines) + "\n")
print("Generated", len(digest["cases"]) + len(ime["cases"]), "saved-result checks")
