# Hardware and toolchains

## Legacy development environments

| Artifact | Historical environment | Notes |
| --- | --- | --- |
| MCU projects | Freescale CodeWarrior with Processor Expert | Targets MCF51QE128 / ColdFire V1 |
| PCB projects | Altium Designer | Binary source and fabrication outputs |
| Operator visualizer | National Instruments LabVIEW | Binary `.vi` |
| Spectrum analysis | MATLAB/Simulink | Binary `.slx` |
| Desktop experiments | Python 3.4 | Uses old serial and NMEA packages |

Exact modern-version compatibility has not been established. Open original
binary artifacts on copies and disable automatic upgrades until backups exist.

## Principal sensors

The thesis and firmware identify these devices or interfaces:

- MPU-6050 inertial measurement unit over I²C;
- HMC6352 digital compass over I²C;
- DS18B20 external temperature sensor over 1-Wire;
- MPX5700AP pressure sensor through an ADC path;
- water-presence digital inputs;
- battery-voltage monitoring through an ADC path.

## Principal actuators

- four bidirectional brushless-motor ESC channels;
- pan and tilt camera servos;
- two high-intensity LED channels;
- status and handshake indicators.

## Reuse checklist

Before manufacturing or energizing any archived design:

1. Review every schematic net and PCB rule in a current Altium environment.
2. Confirm component availability, substitutions, voltage ratings, polarity,
   creepage, current capacity, and thermal limits.
3. Recreate the bill of materials from source rather than trusting old exports.
4. Run current design-rule and electrical-rule checks.
5. Compare fabrication exports to source and obtain a manufacturer review.
6. Bring up with current limiting, fusing, isolated loads, and restrained motors.
7. Recalibrate every sensor and actuator.

No repository check replaces professional electrical, mechanical, pressure, or
marine-safety review.
