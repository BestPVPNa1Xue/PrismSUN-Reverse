"""Check protected hashes, build freshness, links and independent offline CRC values."""
import hashlib
import json
import os
import re
import struct
import subprocess
import sys
import zlib
from pathlib import Path

root = Path(__file__).resolve().parents[1]
workspace = root.parents[1]
evidence = root / "evidence"
def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()
def read(path):
    return json.loads(path.read_text(encoding="utf-8-sig"))
def write(path, obj):
    path.write_text(json.dumps(obj, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")

checks = []
def check(name, success, detail=None):
    checks.append(dict(name=name, passed=bool(success), detail=detail))

before = read(evidence / "resume-before.json")
after = {name: digest(workspace / name) for name in before}
write(evidence / "resume-after.json", after)
for name, expected in before.items():
    check("protected: " + name, after[name] == expected)
check("sample identity", after["libprism-sun.so"] ==
      "92e7d4adda7e222aa9dce389009a186adabb2602b80d618d417e0f6d509adaf4")
build = read(evidence / "build.json")
for output in build["outputs"]:
    path = Path(output["Path"])
    check("build hash: " + path.name, path.exists() and digest(path).lower() == output["Hash"].lower())
for name, key, count in [("host-tests.json", "checks", 73), ("jni-tests.json", "scenarios", 8)]:
    result = read(evidence / name)
    check(name, result["result"] == "PASS" and result[key] == count)

docs = list(root.glob("*.md")) + [evidence / "INDEX.md"]
for doc in docs:
    for link in re.findall(r"\]\(([^)]+)\)", doc.read_text(encoding="utf-8")):
        if "://" in link or link.startswith("#"):
            continue
        target = (doc.parent / link.split("#", 1)[0]).resolve()
        # verification and manifest are generated at the end of this pass.
        exists = target.exists() or target in [evidence / "verification.json", evidence / "offline-baseline.json", root / "manifest.json"]
        check("link: " + doc.name + " -> " + link, exists)

env = os.environ.copy()
env["PATH"] = str(Path(build["hostCompiler"]).parent) + os.pathsep + env.get("PATH", "")
run = subprocess.run([str(root / "build/host/prism_environment.exe"), str(workspace / "libprism-sun.so")],
                     capture_output=True, text=True, env=env, check=True)
actual = [[int(x) for x in row] for row in re.findall(r"section=(\d+) offset=(\d+) size=(\d+) crc32_bswap=(\d+)", run.stdout)]
blob = (workspace / "libprism-sun.so").read_bytes()
shoff = struct.unpack_from("<Q", blob, 40)[0]
stride, count = struct.unpack_from("<HH", blob, 58)
expected = []
for i in range(count):
    sh = shoff + i * stride
    flags = struct.unpack_from("<Q", blob, sh + 8)[0]
    offset, size = struct.unpack_from("<QQ", blob, sh + 24)
    if flags & 4:
        crc = int.from_bytes(zlib.crc32(blob[offset:offset + size]).to_bytes(4, "big"), "little")
        expected.append([i, offset, size, crc])
        if len(expected) == 2:
            break
write(evidence / "offline-baseline.json", dict(result="PASS" if actual == expected else "FAIL",
      scope="New C++ offline parser vs Python struct/zlib on original ELF file bytes; original code not executed",
      stdout=run.stdout, actual=actual, expected=expected))
check("offline ELF baseline independent oracle", actual == expected and len(actual) == 2)

sources = [p for folder in ["src", "tests", "scripts"] for p in (root / folder).glob("*") if p.is_file()]
sources += [root / "CMakeLists.txt"]
dependencies = [root.parent / p for p in ["src/observed_models.cpp", "src/observed_models.h",
    "src/class_probe_model.cpp", "src/class_probe_model.h", "accessibility/src/accessibility_env.cpp",
    "accessibility/src/accessibility_env.hpp"]]
latest = max(p.stat().st_mtime for p in sources if p.suffix in [".cpp", ".hpp", ".h", ".inc"])
for output in build["outputs"]:
    check("build freshness: " + Path(output["Path"]).name, Path(output["Path"]).stat().st_mtime >= latest)
files = sources + dependencies + docs + list(evidence.glob("*.json"))
files += [Path(o["Path"]) for o in build["outputs"]]
exclude = {evidence / "verification.json", evidence / "rea-evidence-2026-10-16.json"}
manifest = {str(p.relative_to(workspace)).replace("\\", "/"): digest(p) for p in files if p not in exclude}
write(root / "manifest.json", dict(sha256=manifest, note="Manifest excludes itself, verification, historical REA dossier and IDBs"))
check("manifest files hashed", all(digest(workspace / path) == h for path, h in manifest.items()), len(manifest))
result = dict(result="PASS" if all(c["passed"] for c in checks) else "FAIL", checks=checks,
              protected_before=before, protected_after=after, host_checks=73, jni_mock_scenarios=8,
              android="compiled only; not deployed or executed", reverse_engineering_backend="IDA Pro MCP only")
write(evidence / "verification.json", result)
print(result["result"], len(checks), "delivery checks;", len(manifest), "manifest files")
for c in checks:
    if not c["passed"]:
        print("FAILED", c["name"])
sys.exit(0 if result["result"] == "PASS" else 1)
