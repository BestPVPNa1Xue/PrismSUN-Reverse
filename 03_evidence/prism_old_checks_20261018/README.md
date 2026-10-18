# Evidence index

All addresses refer to the unpacked ELF, image base 0. `ida-functions.json` preserves IDA pseudocode including bad-SP warnings; `ida-assembly.json` preserves the selected instruction listings clipped to unwind function ranges. The report explains corrections supported by these listings and fixtures.

`strings.json` contains original getter/converter executions. `*-fixtures.json` record original ARM64 branches with explicit synthetic JNI/I/O/libc boundaries. `core-tests.json`, `jni-tests.json`, `build.json` record reconstructed C++ verification. The protected-file records demonstrate that the four prior sample/database files stayed byte-identical.

The scripts under `verification/` need Python, pyelftools and Unicorn. Set `PRISM_OLD_SAMPLE` to the unpacked sample from the release; SHA-256 is in the report. Example:

```powershell
$env:PRISM_OLD_SAMPLE='D:/archive/06_samples/prism_old/libprism-old-small.unpacked.so'
python ./verification/verify_strings.py
python ./verification/debug_fixture.py
python ./verification/maps_fixture.py
python ./verification/jni_fixture.py
python ./verification/reflection_fixture.py
```

Fixture scripts write fresh records in this directory. They never forward a syscall or JNI operation to a target process. The instruction budget bounds execution. String getter bodies are executed in the string check; JNI branch fixtures substitute those already-verified strings to keep each run small. Exact instruction counts can vary with fixture instrumentation.

The full release includes one current annotated IDB and byte-exact previous overview evidence. Prior manifests describe their historical layout; archive omissions are recorded in BUNDLE.json.
