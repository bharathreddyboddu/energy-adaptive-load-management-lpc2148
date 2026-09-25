# Energy Adaptive Load Management using LPC2148

A microcontroller-based load monitoring and control system using
the LPC2148, ADC, current sensing, relays, ULN2003A relay driver,
and a 16×2 LCD.

## Project Overview

The system monitors the electrical loading condition through a
current sensor. The sensor output is converted into a digital
value using the LPC2148 ADC.

Based on predefined threshold levels, the microcontroller
controls multiple loads through relays.

The LCD displays the ADC value and the corresponding load status.

## System Flow

Current Sensor
↓
LPC2148 ADC
↓
Load Condition Detection
↓
Threshold-based Decision
↓
ULN2003A Relay Driver
↓
Relay-controlled Loads
↓
LCD Status Display

## Hardware

- LPC2148
- Current Sensor
- ULN2003A Relay Driver
- 4-Channel Relay
- 16×2 LCD
- LED Loads
- Power Supply

## Software and Tools

- Embedded C
- Keil µVision
- Proteus 8 Professional
- Flash Magic

## Working

The LPC2148 reads the analog output from the current sensor
through its ADC.

The ADC produces a 10-bit digital value from 0 to 1023.

The system uses threshold levels to classify the loading
condition and control the connected loads.

### Load Conditions

| ADC Range | Load Condition | Relay Action |
|---|---|---|
| < 520 | Low load | All loads ON |
| 520–535 | Medium load | Load 4 OFF |
| 535–545 | High load | Loads 3 and 4 OFF |
| > 545 | Very high load | Only Load 1 ON |

## Results

The system was tested both in Proteus simulation and using
the hardware setup.

Different load conditions produced different ADC values,
and the LPC2148 controlled the relays accordingly.

## Project Files

- `src/` - Embedded C source code
- `simulation/` - Proteus circuit and simulation files
- `hardware/` - Hardware setup and output images
- `docs/` - Project documentation

