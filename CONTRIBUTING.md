# Contributing

Thank you for helping preserve and explain the X-Sub telemetry system.

## Before opening a change

Use an issue to discuss changes to firmware behavior, PCB connectivity,
manufacturing data, protocol semantics, or licensing. Documentation corrections
and isolated maintenance-tool fixes may go directly to a pull request.

## Development setup

The maintained validation surface requires Python 3.11 or newer and has no
third-party runtime dependencies.

```bash
git clone https://github.com/X-Sub/Telemetry-System.git
cd Telemetry-System
python -m pip install --requirement requirements-dev.txt
ruff check tools tests scripts
ruff format --check tools tests scripts
python -m unittest discover -s tests -v
python scripts/verify_repository.py
```

Legacy artifacts require their original or compatible proprietary tools. See
[`docs/HARDWARE.md`](docs/HARDWARE.md). A successful modern Python test run does
not validate the firmware, PCB, LabVIEW, or Simulink projects.

## Change policy

- Preserve historical files unless the change has a documented archival reason.
- Place maintained Python code in `tools/` and tests in `tests/`.
- Keep new user-facing prose, names, identifiers, and comments in English.
- Avoid dependencies when the standard library is sufficient.
- Add tests for protocol behavior, including invalid lengths and terminators.
- Update documentation and the changelog with behavior changes.
- Update the asset manifest only for intentional changes to listed artifacts.

## Commit and pull-request style

Use Conventional Commit subjects, for example:

```text
docs: clarify command-frame byte layout
fix(protocol): reject out-of-range actuator values
```

Every pull request should explain:

- why the change is needed;
- which maintained or historical artifacts it touches;
- how it was validated;
- whether proprietary tools or physical hardware were unavailable.

By participating, you agree to follow the
[`CODE_OF_CONDUCT.md`](CODE_OF_CONDUCT.md).
