# AGENTS.md

## Purpose

This repository preserves the X-Sub telemetry-system degree project. Changes
must improve discoverability, safety, reproducibility, or the modern inspection
tools without rewriting historical evidence.

## Repository map

- `MCU Firmware/`: legacy Freescale MCF51QE128 projects.
- `PCB/`: Altium source and fabrication artifacts.
- `Python Data Receiver-Transmitter/`: original Python 3.4 experiments.
- `LabView Visualizer/`: original LabVIEW operator interface.
- `Spectrum Analyser/`: original Simulink and Arduino experiments.
- `tools/`: maintained, dependency-free Python protocol tools.
- `tests/`: tests for maintained Python code.
- `docs/`: current English documentation and integrity manifest.

## Ground rules

1. Treat the original engineering artifacts as read-only unless a task
   explicitly requires a reviewed hardware or firmware correction.
2. Never regenerate or normalize proprietary binary files casually.
3. Never commit IDE workspaces, Altium history, previews, autosaves, logs,
   bytecode, credentials, or captured operational telemetry.
4. Put new maintained tooling in `tools/`, use Python 3.11+, type hints, and the
   standard library unless a dependency has a clear benefit.
5. Keep public documentation in English. Preserve original Spanish text inside
   historical source and the thesis.
6. Clearly separate measured facts, thesis-derived facts, and assumptions.
7. Do not claim that the archived vehicle stack is production-ready.

## Required checks

Run before every commit:

```bash
python -m pip install --requirement requirements-dev.txt
ruff check tools tests scripts
ruff format --check tools tests scripts
python -m unittest discover -s tests -v
python scripts/verify_repository.py
git diff --check
```

If a primary artifact intentionally changes, update
`docs/ASSET_MANIFEST.sha256` in the same commit and explain why in the pull
request.

## Hardware safety

Do not instruct users to energize thrusters or battery systems without current
limits, a physical emergency stop, restrained hardware, and qualified
supervision. Treat all archived calibration and electrical limits as
unverified.

## Pull requests

- Use focused, signed commits and Conventional Commit subjects.
- Explain affected artifacts and tool versions.
- Include validation evidence and note any checks that require proprietary
  software.
- Never bypass branch protection or required checks.
