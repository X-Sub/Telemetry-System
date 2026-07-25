"""Tests for the maintained X-Sub protocol helpers."""

from __future__ import annotations

import contextlib
import io
import json
import unittest

from tools.xsub_protocol import (
    COMMAND_FRAME_SIZE,
    TELEMETRY_FRAME_SIZE,
    CommandFrame,
    ProtocolError,
    TelemetryFrame,
    main,
    signed_16,
)


class TelemetryFrameTests(unittest.TestCase):
    def setUp(self) -> None:
        self.payload = bytes(
            [
                1,
                0,
                2,
                0,
                3,
                0,
                4,
                0,
                5,
                0,
                6,
                0,
                7,
                0,
                8,
                0,
                9,
                0,
                10,
                0,
                11,
                0,
                12,
                13,
                14,
                26,
                0xFF,
            ]
        )

    def test_decode_complete_frame(self) -> None:
        frame = TelemetryFrame.from_bytes(self.payload)

        self.assertEqual(len(self.payload), TELEMETRY_FRAME_SIZE)
        self.assertEqual(frame.status, 1)
        self.assertEqual(frame.external_temperature, 2)
        self.assertEqual(frame.internal_temperature, 3)
        self.assertEqual(frame.external_pressure, 4)
        self.assertEqual(frame.acceleration_x, 5)
        self.assertEqual(frame.acceleration_y, 6)
        self.assertEqual(frame.acceleration_z, 7)
        self.assertEqual(frame.angular_velocity_x, 8)
        self.assertEqual(frame.angular_velocity_y, 9)
        self.assertEqual(frame.angular_velocity_z, 10)
        self.assertEqual(frame.linear_velocity, 11)
        self.assertEqual(frame.compass_heading, 12)
        self.assertEqual(frame.water_presence, 13)
        self.assertEqual(frame.battery_level, 14)
        self.assertEqual(frame.integrity_byte, 26)

    def test_decode_hex(self) -> None:
        self.assertEqual(TelemetryFrame.from_hex(self.payload.hex()).status, 1)

    def test_reject_wrong_type(self) -> None:
        with self.assertRaisesRegex(ProtocolError, "must be bytes"):
            TelemetryFrame.from_bytes(bytearray(self.payload))  # type: ignore[arg-type]

    def test_reject_wrong_length(self) -> None:
        with self.assertRaisesRegex(ProtocolError, "27 bytes"):
            TelemetryFrame.from_bytes(self.payload[:-1])

    def test_reject_wrong_terminator(self) -> None:
        with self.assertRaisesRegex(ProtocolError, "must end"):
            TelemetryFrame.from_bytes(self.payload[:-1] + b"\x00")

    def test_reject_invalid_hex(self) -> None:
        with self.assertRaisesRegex(ProtocolError, "valid hexadecimal"):
            TelemetryFrame.from_hex("not-hex")

    def test_to_dict(self) -> None:
        self.assertEqual(
            TelemetryFrame.from_bytes(self.payload).to_dict()["battery_level"], 14
        )


class CommandFrameTests(unittest.TestCase):
    def test_encode_command(self) -> None:
        frame = CommandFrame(1, 2, 3, 4, 5, 6, 7, 8, 9).to_bytes()

        self.assertEqual(len(frame), COMMAND_FRAME_SIZE)
        self.assertEqual(frame, bytes([1, 2, 3, 4, 5, 6, 7, 8, 9, 0xFF]))

    def test_encode_hex(self) -> None:
        self.assertEqual(
            CommandFrame(0, 1, 2, 3, 4, 5, 6, 7, 8).to_hex(), "000102030405060708ff"
        )

    def test_reject_out_of_range_value(self) -> None:
        with self.assertRaisesRegex(ProtocolError, "range"):
            CommandFrame(256, 1, 2, 3, 4, 5, 6, 7, 8).to_bytes()

    def test_reject_boolean(self) -> None:
        with self.assertRaisesRegex(ProtocolError, "integer"):
            CommandFrame(True, 1, 2, 3, 4, 5, 6, 7, 8).to_bytes()


class HelperTests(unittest.TestCase):
    def test_signed_16(self) -> None:
        self.assertEqual(signed_16(0), 0)
        self.assertEqual(signed_16(0x7FFF), 32767)
        self.assertEqual(signed_16(0x8000), -32768)
        self.assertEqual(signed_16(0xFFFF), -1)

    def test_signed_16_rejects_invalid_values(self) -> None:
        for value in (-1, 0x10000, True):
            with self.subTest(value=value), self.assertRaises(ProtocolError):
                signed_16(value)

    def test_decode_cli(self) -> None:
        payload = bytes([0] * 26 + [0xFF])
        output = io.StringIO()
        with contextlib.redirect_stdout(output):
            self.assertEqual(main(["decode", payload.hex()]), 0)
        self.assertEqual(json.loads(output.getvalue())["status"], 0)

    def test_command_cli(self) -> None:
        output = io.StringIO()
        with contextlib.redirect_stdout(output):
            result = main(
                [
                    "command",
                    "--motors",
                    "1",
                    "2",
                    "3",
                    "4",
                    "--pan",
                    "5",
                    "--tilt",
                    "6",
                    "--lights",
                    "7",
                    "8",
                    "--status",
                    "9",
                ]
            )
        self.assertEqual(result, 0)
        self.assertEqual(output.getvalue().strip(), "010203040506070809ff")


if __name__ == "__main__":
    unittest.main()
