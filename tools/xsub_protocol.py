"""Encode and decode the legacy X-Sub serial protocol.

The layouts are derived directly from the archived MCF51QE128 firmware. Sensor
values remain raw because scaling and calibration are outside the byte protocol.
"""

from __future__ import annotations

import argparse
import json
from collections.abc import Sequence
from dataclasses import asdict, dataclass
from typing import Final

FRAME_TERMINATOR: Final = 0xFF
TELEMETRY_FRAME_SIZE: Final = 27
COMMAND_FRAME_SIZE: Final = 10


class ProtocolError(ValueError):
    """Raised when a frame does not match the archived wire format."""


def _validate_byte(name: str, value: int) -> int:
    if not isinstance(value, int) or isinstance(value, bool):
        raise ProtocolError(f"{name} must be an integer")
    if not 0 <= value <= 0xFF:
        raise ProtocolError(f"{name} must be in the range 0..255")
    return value


def _unsigned_16(frame: bytes, offset: int) -> int:
    return int.from_bytes(frame[offset : offset + 2], byteorder="big", signed=False)


def signed_16(value: int) -> int:
    """Interpret one unsigned 16-bit value as signed two's complement."""

    if (
        not isinstance(value, int)
        or isinstance(value, bool)
        or not 0 <= value <= 0xFFFF
    ):
        raise ProtocolError("value must be an integer in the range 0..65535")
    return value - 0x10000 if value & 0x8000 else value


@dataclass(frozen=True, slots=True)
class TelemetryFrame:
    """One 27-byte telemetry frame containing raw sensor values."""

    status: int
    external_temperature: int
    internal_temperature: int
    external_pressure: int
    acceleration_x: int
    acceleration_y: int
    acceleration_z: int
    angular_velocity_x: int
    angular_velocity_y: int
    angular_velocity_z: int
    linear_velocity: int
    compass_heading: int
    water_presence: int
    battery_level: int
    integrity_byte: int

    @classmethod
    def from_bytes(cls, frame: bytes) -> TelemetryFrame:
        """Decode one exact frame and validate its terminator."""

        if not isinstance(frame, bytes):
            raise ProtocolError("telemetry frame must be bytes")
        if len(frame) != TELEMETRY_FRAME_SIZE:
            raise ProtocolError(
                f"telemetry frame must contain {TELEMETRY_FRAME_SIZE} bytes; "
                f"received {len(frame)}"
            )
        if frame[-1] != FRAME_TERMINATOR:
            raise ProtocolError(
                f"telemetry frame must end in 0x{FRAME_TERMINATOR:02x}; "
                f"received 0x{frame[-1]:02x}"
            )

        return cls(
            status=frame[0],
            external_temperature=_unsigned_16(frame, 1),
            internal_temperature=_unsigned_16(frame, 3),
            external_pressure=_unsigned_16(frame, 5),
            acceleration_x=_unsigned_16(frame, 7),
            acceleration_y=_unsigned_16(frame, 9),
            acceleration_z=_unsigned_16(frame, 11),
            angular_velocity_x=_unsigned_16(frame, 13),
            angular_velocity_y=_unsigned_16(frame, 15),
            angular_velocity_z=_unsigned_16(frame, 17),
            linear_velocity=_unsigned_16(frame, 19),
            compass_heading=_unsigned_16(frame, 21),
            water_presence=frame[23],
            battery_level=frame[24],
            integrity_byte=frame[25],
        )

    @classmethod
    def from_hex(cls, value: str) -> TelemetryFrame:
        """Decode a hexadecimal telemetry frame."""

        try:
            frame = bytes.fromhex(value)
        except ValueError as error:
            raise ProtocolError("telemetry input must be valid hexadecimal") from error
        return cls.from_bytes(frame)

    def to_dict(self) -> dict[str, int]:
        """Return a JSON-ready mapping."""

        return asdict(self)


@dataclass(frozen=True, slots=True)
class CommandFrame:
    """One 10-byte actuator command frame."""

    motor_1: int
    motor_2: int
    motor_3: int
    motor_4: int
    camera_pan: int
    camera_tilt: int
    light_1: int
    light_2: int
    status: int

    def to_bytes(self) -> bytes:
        """Validate and encode this command in firmware byte order."""

        values = (
            ("motor_1", self.motor_1),
            ("motor_2", self.motor_2),
            ("motor_3", self.motor_3),
            ("motor_4", self.motor_4),
            ("camera_pan", self.camera_pan),
            ("camera_tilt", self.camera_tilt),
            ("light_1", self.light_1),
            ("light_2", self.light_2),
            ("status", self.status),
        )
        return bytes(_validate_byte(name, value) for name, value in values) + bytes(
            [FRAME_TERMINATOR]
        )

    def to_hex(self) -> str:
        """Return a compact lowercase hexadecimal representation."""

        return self.to_bytes().hex()


def _build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        prog="xsub-protocol",
        description="Inspect the archived X-Sub telemetry protocol.",
    )
    subparsers = parser.add_subparsers(dest="operation", required=True)

    decode = subparsers.add_parser("decode", help="decode one 27-byte telemetry frame")
    decode.add_argument("frame", help="hexadecimal telemetry frame")

    command = subparsers.add_parser("command", help="encode one 10-byte command frame")
    command.add_argument(
        "--motors",
        nargs=4,
        type=int,
        required=True,
        metavar=("M1", "M2", "M3", "M4"),
    )
    command.add_argument("--pan", type=int, required=True)
    command.add_argument("--tilt", type=int, required=True)
    command.add_argument(
        "--lights", nargs=2, type=int, required=True, metavar=("L1", "L2")
    )
    command.add_argument("--status", type=int, default=0)
    return parser


def main(argv: Sequence[str] | None = None) -> int:
    """Run the protocol command-line interface."""

    parser = _build_parser()
    args = parser.parse_args(argv)

    try:
        if args.operation == "decode":
            print(
                json.dumps(
                    TelemetryFrame.from_hex(args.frame).to_dict(),
                    indent=2,
                    sort_keys=True,
                )
            )
        else:
            frame = CommandFrame(
                *args.motors,
                camera_pan=args.pan,
                camera_tilt=args.tilt,
                light_1=args.lights[0],
                light_2=args.lights[1],
                status=args.status,
            )
            print(frame.to_hex())
    except ProtocolError as error:
        parser.error(str(error))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
