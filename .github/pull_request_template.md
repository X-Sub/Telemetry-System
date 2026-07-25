## Summary

<!-- What changed and why? -->

## Scope

- [ ] Maintained Python tooling
- [ ] Documentation or repository automation
- [ ] Legacy firmware
- [ ] PCB or fabrication artifacts
- [ ] LabVIEW, Simulink, or other binary artifacts

## Validation

- [ ] `ruff check tools tests scripts`
- [ ] `ruff format --check tools tests scripts`
- [ ] `python -m unittest discover -s tests -v`
- [ ] `python scripts/verify_repository.py`
- [ ] `git diff --check`
- [ ] Relevant proprietary-tool checks, or an explanation of why they were unavailable

## Safety and integrity

- [ ] No credentials, private telemetry, personal data, or license keys are included
- [ ] Hardware implications and limitations are documented
- [ ] `docs/ASSET_MANIFEST.sha256` was updated if a listed artifact changed
