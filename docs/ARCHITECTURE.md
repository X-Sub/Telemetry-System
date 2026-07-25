# System architecture

## Scope

This description is derived from the archived firmware and the 2016 thesis. It
documents the intended prototype architecture; it is not a current as-built
verification.

## Data path

The vehicle-side MCF51QE128 controller centralizes low-level acquisition and
actuation. It samples inertial, magnetic, temperature, pressure, water-presence,
and battery signals. A 27-byte frame is sent over UART to an onboard pcDuino.
The onboard computer was intended to log the data and relay it to a surface
station. Commands travel in the reverse direction as 10-byte frames.

```text
                                      Ethernet / vehicle link
Sensors ──► MCF51QE128 ──UART──► onboard pcDuino ─────────────► surface station
                  ▲                       │                           │
                  └──── PWM / GPIO        └──── logging              └ visualization
                        actuators
```

## Embedded controller

The main firmware project is under
`MCU Firmware/X-Sub MCU Firmware/`. Processor Expert generated peripheral
drivers while project-specific logic lives mainly in `Sources/xSub.c`,
`Sources/xSub.h`, `Sources/OneWire.c`, and `Sources/main.c`.

The archived configuration shows:

- MCF51QE128 32-bit ColdFire V1 microcontroller;
- I²C acquisition for MPU-6050 and HMC6352 devices;
- 1-Wire support for a DS18B20 temperature sensor;
- ADC channels for pressure and battery measurement;
- digital water-presence inputs;
- PWM outputs for four ESCs, two camera servos, and two lights;
- status LEDs and a UART link to the onboard computer.

## Boards

The project contains two principal Altium designs:

1. `PCB/X-Sub_Board/` - acquisition, control, expansion, and sensor interfaces.
2. `PCB/pcDuino Link Board/` - power distribution and signal interconnection
   between the main controller and pcDuino.

Manufacturing outputs are preserved where they existed. They must be reviewed
against the source design and a current fabrication rule set before reuse.

## Operator-side experiments

The Python 3.4 scripts demonstrate early serial, GPS, threading, and logging
work. LabVIEW and Simulink artifacts demonstrate visualization and inertial
spectrum-analysis experiments. These parts are prototypes, not an integrated
current application.

## Maintained boundary

Only the documentation, repository automation, integrity checks, and
`tools/xsub_protocol.py` are maintained with current open-source tooling. Legacy
project compatibility is documented but not asserted.
