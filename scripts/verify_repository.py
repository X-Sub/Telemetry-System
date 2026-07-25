#!/usr/bin/env python3
"""Verify repository hygiene and primary historical artifact integrity."""

from __future__ import annotations

import hashlib
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
MANIFEST = ROOT / "docs" / "ASSET_MANIFEST.sha256"
REQUIRED = (
    "AGENTS.md",
    "CLAUDE.md",
    "CONTRIBUTING.md",
    "LICENSE",
    "README.md",
    "SECURITY.md",
    "docs/ARCHITECTURE.md",
    "docs/PROTOCOL.md",
    "tools/xsub_protocol.py",
)
FORBIDDEN_DIRECTORY_NAMES = {"History", "__Previews", "__pycache__", ".metadata"}
FORBIDDEN_SUFFIXES = {".autosave", ".pyc", ".pyo"}
ACTION_PATTERN = re.compile(r"^\s*uses:\s*[^@\s]+@([^#\s]+)")
COMMIT_SHA_PATTERN = re.compile(r"^[0-9a-f]{40}$")


def digest(path: Path) -> str:
    value = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            value.update(chunk)
    return value.hexdigest()


def verify_required_files(errors: list[str]) -> None:
    for relative_path in REQUIRED:
        if not (ROOT / relative_path).is_file():
            errors.append(f"missing required file: {relative_path}")


def verify_hygiene(errors: list[str]) -> None:
    result = subprocess.run(
        ["git", "ls-files", "-z"],
        cwd=ROOT,
        check=True,
        capture_output=True,
    )
    for encoded_path in result.stdout.split(b"\0"):
        if not encoded_path:
            continue
        relative_path = encoded_path.decode("utf-8")
        path = ROOT / relative_path
        if any(
            part in FORBIDDEN_DIRECTORY_NAMES or part.startswith("Project Logs for ")
            for part in path.parts
        ):
            errors.append(f"forbidden generated path: {relative_path}")
        if (
            path.suffix in FORBIDDEN_SUFFIXES
            or path.name == "logger.txt"
            or path.stat().st_size > 10 * 1024 * 1024
        ):
            errors.append(f"forbidden generated or oversized file: {relative_path}")


def verify_manifest(errors: list[str]) -> None:
    for line_number, line in enumerate(
        MANIFEST.read_text(encoding="utf-8").splitlines(), start=1
    ):
        if not line or line.startswith("#"):
            continue
        try:
            expected, relative_path = line.split("  ", maxsplit=1)
        except ValueError:
            errors.append(f"invalid manifest line {line_number}")
            continue
        path = ROOT / relative_path
        if not path.is_file():
            errors.append(f"manifest target is missing: {relative_path}")
        elif digest(path) != expected:
            errors.append(f"artifact hash mismatch: {relative_path}")


def verify_action_pins(errors: list[str]) -> None:
    for workflow in (ROOT / ".github" / "workflows").glob("*.yml"):
        for line_number, line in enumerate(
            workflow.read_text(encoding="utf-8").splitlines(), start=1
        ):
            match = ACTION_PATTERN.match(line)
            if match and not COMMIT_SHA_PATTERN.fullmatch(match.group(1)):
                errors.append(
                    f"mutable action reference: {workflow.relative_to(ROOT)}:{line_number}"
                )


def main() -> int:
    errors: list[str] = []
    verify_required_files(errors)
    verify_hygiene(errors)
    verify_manifest(errors)
    verify_action_pins(errors)

    if errors:
        print("Repository verification failed:", file=sys.stderr)
        for error in errors:
            print(f"- {error}", file=sys.stderr)
        return 1

    print("Repository verification passed.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
