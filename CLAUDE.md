# CLAUDE.md

Read and follow [`AGENTS.md`](AGENTS.md) before making changes.

This is a historical, hardware-adjacent repository. Preserve original research
artifacts, avoid speculative rewrites, and keep new documentation in English.
The maintained surface is the dependency-free Python protocol utility in
`tools/`, its tests, repository checks, and documentation.

Before proposing a change, run:

```bash
python -m pip install --requirement requirements-dev.txt
ruff check tools tests scripts
ruff format --check tools tests scripts
python -m unittest discover -s tests -v
python scripts/verify_repository.py
git diff --check
```

Never place credentials, real mission telemetry, personal data, or proprietary
tool licenses in the repository. Never describe the legacy control stack as
safe for unattended or production operation.
