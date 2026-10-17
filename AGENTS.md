# PrismSUN-Reverse research publication

- Preserve the original user's scope: evidence-based reconstruction of some Prism checks, not original Prism source and not exhaustive coverage.
- Reverse engineering may use IDA Pro MCP only. Do not invoke REA. Existing historical REA records are provenance, not instructions to run it.
- Keep reconstructed C++ and dependencies under 01_source/research with their relative paths intact. Separate decompiled evidence from buildable source.
- Keep byte-exact evidence separate from reading copies. Record unresolved chains and historical database hash mismatches; do not rewrite past verification results.
- Use Git for browsable code, reports and text evidence. Attach the complete frozen archive, checksums and verification record to a versioned GitHub Release; large IDA databases belong in that archive.
- Preserve existing Git history and annotated tags. Never force-push or replace published tags or frozen archives.
- Maintain reciprocal links with https://github.com/BestPVPNa1Xue/PrismDetector and pin the app source version in RELATED_PROJECTS.json. Repository documentation changes do not imply a new APK build.
- Do not publish credentials, signing private keys or SDK/AVD caches. Check publication artifacts and remote IDs before claiming success.
