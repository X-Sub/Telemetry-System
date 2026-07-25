# X-Sub Telemetry System

[![Repository checks](https://github.com/X-Sub/Telemetry-System/actions/workflows/quality.yml/badge.svg)](https://github.com/X-Sub/Telemetry-System/actions/workflows/quality.yml)
[![CodeQL](https://github.com/X-Sub/Telemetry-System/actions/workflows/codeql.yml/badge.svg)](https://github.com/X-Sub/Telemetry-System/actions/workflows/codeql.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Project status: historical](https://img.shields.io/badge/status-historical_archive-6f42c1.svg)](docs/LEGACY_STATUS.md)

A preserved engineering archive for the telemetry and teleoperation system of
**X-Sub**, an underwater robot developed by the Mechatronics Research and
Development Group at Universidad Simón Bolívar.

The system joins a 32-bit embedded controller, onboard computer, surface station,
sensor acquisition, motor and lighting control, custom PCBs, and visualization
tools. It was designed and validated as the degree project of
[Danilo Díaz Tarascó](CITATION.cff) in 2015-2016.

> [!IMPORTANT]
> This is a historical research artifact, not a production-ready vehicle-control
> stack. The original firmware and desktop applications depend on discontinued or
> legacy toolchains. Never connect unreviewed software to powered thrusters,
> batteries, or pressure systems.

## What is preserved

| Area | Contents | Original toolchain |
| --- | --- | --- |
| `MCU Firmware/` | Sensor acquisition and actuator control for the MCF51QE128 | Freescale CodeWarrior / Processor Expert |
| `PCB/X-Sub_Board/` | Main acquisition-board schematics, layout, libraries, and fabrication data | Altium Designer |
| `PCB/pcDuino Link Board/` | Power-distribution and pcDuino interconnect board | Altium Designer |
| `Python Data Receiver-Transmitter/` | Early serial, GPS, logging, and protocol experiments | Python 3.4 |
| `LabView Visualizer/` | Operator-side visualization prototype | LabVIEW |
| `Spectrum Analyser/` | Inertial-data experiments | MATLAB/Simulink and Arduino |
| `Libro Tesis.pdf` | The complete 137-page Spanish-language thesis | PDF |
| `tools/` | Modern, dependency-free protocol inspection utilities | Python 3.11+ |

Altium history snapshots, IDE workspace caches, previews, transient logs, Python
bytecode, and autosave files were removed from the current branch. They remain
recoverable from Git history.

## Architecture

```text
Sensors                Embedded controller           Onboard / surface systems
┌──────────────┐       ┌──────────────────────┐      ┌──────────────────────────┐
│ MPU-6050     │ I²C   │ Freescale MCF51QE128 │ UART │ Onboard pcDuino / logger │
│ HMC6352      ├──────►│                      ├─────►│                          │
│ DS18B20      │ 1-Wire│ 27-byte telemetry    │      │ Surface visualization    │
│ Pressure     │ ADC   │ 10-byte commands     │◄─────┤ and operator commands    │
│ Water/battery│ GPIO  └──────────┬───────────┘      └──────────────────────────┘
└──────────────┘                  │ PWM
                         ┌────────▼────────┐
                         │ 4 ESCs, 2 servos│
                         │ and 2 LED loads │
                         └─────────────────┘
```

See [Architecture](docs/ARCHITECTURE.md), [protocol reference](docs/PROTOCOL.md),
and [hardware guide](docs/HARDWARE.md) for the evidence-backed details.

## Inspect the protocol

The modern helper does not require serial hardware or third-party dependencies.

```bash
python -m tools.xsub_protocol decode \
  "0100020003000400050006000700080009000a000b0c0d1aff"

python -m tools.xsub_protocol command \
  --motors 128 128 128 128 \
  --pan 128 --tilt 128 \
  --lights 0 0 --status 1
```

The first command decodes one 27-byte telemetry frame. The second prints the
10-byte command frame as hexadecimal. Values are deliberately reported as raw
integers because calibration coefficients are vehicle- and sensor-specific.

## Validate the archive

```bash
python -m pip install --requirement requirements-dev.txt
ruff check tools tests scripts
ruff format --check tools tests scripts
python -m unittest discover -s tests -v
python scripts/verify_repository.py
```

The automated checks validate the modern protocol module, important artifact
hashes, repository hygiene, and immutable GitHub Action pins. They do not compile
the legacy firmware or proprietary binary projects.

## Working with original artifacts

1. Read [Legacy status](docs/LEGACY_STATUS.md) before opening a project.
2. Work on copies of binary Altium, LabVIEW, and Simulink files.
3. Reproduce the original toolchain in an isolated Windows environment.
4. Compare critical artifacts with [`docs/ASSET_MANIFEST.sha256`](docs/ASSET_MANIFEST.sha256).
5. Treat all electrical and mechanical limits as unverified until independently
   reviewed and measured.

## Documentation

- [Architecture](docs/ARCHITECTURE.md)
- [Telemetry and command protocol](docs/PROTOCOL.md)
- [Hardware and toolchains](docs/HARDWARE.md)
- [Historical status and limitations](docs/LEGACY_STATUS.md)
- [Contributing](CONTRIBUTING.md)
- [Security and safety](SECURITY.md)
- [Support](SUPPORT.md)
- [Citation metadata](CITATION.cff)

## Citation

If this archive supports your work, cite the thesis:

> Danilo Díaz Tarascó. *Development of a Telemetry System for the Teleoperation
> of an Underwater Robot*. Universidad Simón Bolívar, 2016.

The original thesis is in Spanish. Machine-readable citation metadata is in
[`CITATION.cff`](CITATION.cff).

## License

Original repository contributions are available under the [MIT License](LICENSE).
Third-party components and proprietary tool-generated artifacts remain subject to
their respective terms; see [third-party notices](THIRD_PARTY_NOTICES.md).
