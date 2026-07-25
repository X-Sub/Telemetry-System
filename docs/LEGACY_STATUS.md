# Historical status and limitations

## Status

X-Sub Telemetry System is preserved as a historical engineering and educational
archive. Development occurred primarily in 2015, and the accompanying thesis
was submitted in April 2016. A PCB update was committed in 2023.

The archive demonstrates a complete prototype design process, including
requirements, architecture, firmware, PCB design, fabrication outputs,
operator-side experiments, and academic documentation.

## What is maintained

- English documentation;
- repository policy and security configuration;
- GitHub Actions checks;
- primary-artifact integrity hashes;
- the dependency-free Python protocol inspector and its tests.

## What is not maintained

- proprietary project-format compatibility;
- the original Python 3.4 applications;
- embedded firmware builds;
- hardware sourcing or fabrication;
- vehicle calibration;
- live control, navigation, or mission operation.

## Known technical limitations

- The serial protocol has a terminator but no reliable checksum or
  authentication.
- The original Python code contains broad exception handling, hard-coded Windows
  paths and ports, and legacy dependencies.
- Firmware was generated partly by an old Processor Expert toolchain.
- Binary project formats may migrate irreversibly in current vendor software.
- Current electrical rules, component lifecycles, and fabrication tolerances
  have not been revalidated.

## Archival cleanup

The current branch omits generated IDE workspace state, Altium edit history,
previews, project logs, runtime logs, bytecode, and autosaves. Those files were
not authoritative source or release artifacts and remain available in earlier
Git commits.
