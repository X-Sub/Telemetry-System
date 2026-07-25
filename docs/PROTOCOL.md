# Serial protocol reference

This reference is derived from
`MCU Firmware/X-Sub MCU Firmware/Sources/xSub.c`,
`Sources/Events.c`, and `Init.c`.

## Transport

- Original configured baud rate: 115200 baud in the Python experiment.
- Byte order for 16-bit telemetry values: big-endian (high byte, then low byte).
- Telemetry frame length: 27 bytes.
- Command frame length: 10 bytes.
- Both layouts end in `0xFF`.

The archived firmware does not implement framing recovery, escaping,
authentication, replay protection, or a robust checksum. A production protocol
must add those properties.

## Telemetry frame

| Offset | Width | Field |
| ---: | ---: | --- |
| 0 | 1 | Status |
| 1 | 2 | External temperature |
| 3 | 2 | Internal temperature |
| 5 | 2 | External pressure |
| 7 | 2 | Acceleration X |
| 9 | 2 | Acceleration Y |
| 11 | 2 | Acceleration Z |
| 13 | 2 | Angular velocity X |
| 15 | 2 | Angular velocity Y |
| 17 | 2 | Angular velocity Z |
| 19 | 2 | Linear velocity |
| 21 | 2 | Compass heading |
| 23 | 1 | Water-presence state |
| 24 | 1 | Battery level |
| 25 | 1 | Field named `XOR` in firmware |
| 26 | 1 | Terminator (`0xFF`) |

Although byte 25 is named `XOR`, the archived initialization assigns the
constant decimal value `26`; no checksum calculation is visible in the frame
construction path. Consumers must therefore treat it as an integrity placeholder,
not a verified checksum.

The maintained decoder reports raw unsigned values. IMU values may be
interpreted as signed 16-bit two's-complement values with `signed_16()`, but
physical units require sensor configuration and calibration.

## Command frame

| Offset | Width | Field | Raw range |
| ---: | ---: | --- | ---: |
| 0 | 1 | Motor 1 | 0-255 |
| 1 | 1 | Motor 2 | 0-255 |
| 2 | 1 | Motor 3 | 0-255 |
| 3 | 1 | Motor 4 | 0-255 |
| 4 | 1 | Camera pan | 0-255 |
| 5 | 1 | Camera tilt | 0-255 |
| 6 | 1 | Light 1 | 0-255 |
| 7 | 1 | Light 2 | 0-255 |
| 8 | 1 | PC status | 0-255 |
| 9 | 1 | Terminator | `0xFF` |

## Security and safety limitations

Any correctly shaped command can request actuator movement. There is no
authentication, sequence number, timeout encoded in the frame, or cryptographic
integrity. Never expose this protocol directly to an untrusted network or drive
physical actuators from the modern inspection helper.
