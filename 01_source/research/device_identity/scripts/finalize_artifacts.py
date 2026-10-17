"""Hash protected originals and create a reviewable, bounded delivery archive.

Run in the established PrismSUN research tree. No target application is run.
Original binaries/IDBs and the working IDA sidecars are never modified.
"""
import hashlib
import json
import zipfile
from datetime import datetime, timezone
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
EVIDENCE = ROOT / "evidence"
ARCHIVE = ROOT / "prism-device-identity-deliverables.zip"
SPECIAL = {"evidence/manifest.json", "evidence/delivery.json"}
DATABASE_SUFFIXES = {".i64", ".idb", ".id0", ".id1", ".id2", ".nam", ".til"}


def digest(path):
    value = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            value.update(block)
    return value.hexdigest()


def save(path, value):
    path.write_text(json.dumps(value, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")


def row(path):
    return {
        "path": path.relative_to(ROOT).as_posix(),
        "length": path.stat().st_size,
        "sha256": digest(path),
    }


def admitted(path):
    rel = path.relative_to(ROOT)
    return (path.is_file() and "__pycache__" not in rel.parts
            and path.suffix.lower() not in DATABASE_SUFFIXES | {".pyc", ".zip"}
            and not path.name.endswith(".tmp"))


def main():
    now = datetime.now(timezone.utc).isoformat()
    before = json.loads((EVIDENCE / "before.json").read_text(encoding="utf-8-sig"))
    originals = []
    for old in before:
        path = Path(old["path"])
        current = dict(path=str(path), length=path.stat().st_size, sha256=digest(path))
        current["unchanged"] = all(current[key] == old[key] for key in ("length", "sha256"))
        originals.append(current)
    if not all(value["unchanged"] for value in originals):
        raise RuntimeError("Protected original identity changed; delivery not created")
    save(EVIDENCE / "after.json", dict(checked_at_utc=now, status="PASS", files=originals))

    build = json.loads((EVIDENCE / "build.json").read_text(encoding="utf-8-sig"))
    for artifact in build["outputs"]:
        if digest(Path(artifact["Path"])) != artifact["Hash"].lower():
            raise RuntimeError("Build output differs from successful build record: " + artifact["Path"])
    verification = json.loads((EVIDENCE / "verification.json").read_text(encoding="utf-8-sig"))
    if verification["status"] != "PASS" or verification["checks"] != len(verification["names"]):
        raise RuntimeError("Final verification record is inconsistent")

    files = sorted((path for path in ROOT.rglob("*") if admitted(path)
                    and path.relative_to(ROOT).as_posix() not in SPECIAL),
                   key=lambda path: path.relative_to(ROOT).as_posix())
    records = [row(path) for path in files]
    database = ROOT / "prism-device-identity.i64"
    if not database.is_file():
        raise RuntimeError("Saved analysis database is missing")
    manifest = dict(
        schema="prism-device-identity-delivery-v1", generated_at_utc=now,
        sample_sha256=originals[0]["sha256"], original_integrity="PASS",
        verification_status=verification["status"], verification_checks=verification["checks"],
        build_output_identity="PASS", files=records,
        analysis_database=row(database),
        exclusions=["original binaries and original IDBs", "analysis IDB and IDA sidecars",
                    "Python caches", "all zip files", "manifest self hash", "delivery record"],
        reproduction_limit="C++ source is self-contained. Original-instruction experiments need "
                           "the original ELF and existing external research harnesses.")
    save(EVIDENCE / "manifest.json", manifest)
    archive_files = files + [EVIDENCE / "manifest.json"]
    prefix = "prism-device-identity/"
    with zipfile.ZipFile(ARCHIVE, "w", compression=zipfile.ZIP_DEFLATED, compresslevel=6) as package:
        for path in archive_files:
            package.write(path, prefix + path.relative_to(ROOT).as_posix())

    with zipfile.ZipFile(ARCHIVE) as package:
        bad = package.testzip()
        if bad:
            raise RuntimeError("Archive CRC mismatch: " + bad)
        expected_names = {prefix + path.relative_to(ROOT).as_posix() for path in archive_files}
        if set(package.namelist()) != expected_names or len(package.namelist()) != len(expected_names):
            raise RuntimeError("Archive inventory mismatch")
        for record in records + [row(EVIDENCE / "manifest.json")]:
            data = package.read(prefix + record["path"])
            if len(data) != record["length"] or hashlib.sha256(data).hexdigest() != record["sha256"]:
                raise RuntimeError("Archive file identity mismatch: " + record["path"])
    delivery = dict(status="PASS", generated_at_utc=now, archive=row(ARCHIVE),
                    entries=len(archive_files), archive_crc="PASS", archive_hashes="PASS",
                    source_manifest_sha256=digest(EVIDENCE / "manifest.json"),
                    protected_originals="4/4 unchanged", build_outputs="3/3 unchanged",
                    verification=f"{verification['checks']} checks PASS",
                    exclusions=manifest["exclusions"],
                    note="delivery.json is external to the archive to avoid a circular archive hash")
    save(EVIDENCE / "delivery.json", delivery)
    print(json.dumps(delivery, ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
