# Security and safety policy

## Supported surface

Security fixes are accepted for the current default branch, especially for the
maintained protocol utilities and repository automation. The original 2015
firmware, Python 3.4 scripts, and proprietary-tool projects are historical and
are not supported as secure production software.

## Report privately

Use GitHub's private vulnerability reporting feature for vulnerabilities,
credential exposure, unsafe control behavior, or issues that could endanger
hardware or people. Do not include active secrets, sensitive telemetry, or
personal data in a public issue.

Include:

- the affected path and revision;
- impact and realistic attack or failure scenario;
- minimal reproduction steps;
- a suggested mitigation, if available.

## Safety boundary

The repository controls or documents motors, high-current lighting, batteries,
and underwater electronics. Software validation alone does not establish
electrical, mechanical, pressure, or operational safety.

Before physical tests, use qualified supervision, current limiting, restrained
thrusters, fusing, isolation, and a tested emergency stop. Never rely on this
archive as the sole authority for component ratings or safe operating limits.

## Secrets

Never commit API keys, serial numbers tied to individuals, Wi-Fi credentials,
private endpoints, mission logs, or licensed-tool activation data. If a secret
is exposed, revoke it first and then report the incident privately.
