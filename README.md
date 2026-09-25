# Energy Adaptive Load Management using LPC2148

A microcontroller-based load monitoring and control system using the LPC2148, ADC, current sensing, relays, ULN2003A relay driver, and a 16×2 LCD.

## Project Overview

The system monitors the electrical loading condition through a current sensor. The sensor output is converted into a digital value using the LPC2148 ADC.

Based on predefined threshold levels, the microcontroller controls multiple loads through relays. The LCD displays the ADC value and the corresponding load status.

## System Flow

Current Sensor
↓
LPC2148 ADC
↓
Load Condition Detection
↓
Threshold-Based Decision
↓
ULN2003A Relay Driver
↓
Relay-Controlled Loads
↓
16×2 LCD Status Display

## Hardware Used

- LPC2148 Microcontroller
- Current Sensor
- 10-bit ADC
- ULN2003A Relay Driver
- 4-Channel Relay
- 16×2 LCD
- LED Loads
- Breadboard and Connecting Wires
- Power Supply

## Software and Tools

- Embedded C
- Keil µVision
- Proteus 8 Professional
- Flash Magic

## Load Control Logic

The ADC value is used to determine the loading condition.

| ADC Range | Load Control |
|---|---|
| ADC < 530 | L1, L2, L3, L4 ON |
| 530 ≤ ADC < 560 | L4 OFF |
| 560 ≤ ADC < 590 | L3 and L4 OFF |
| ADC ≥ 590 | Only L1 ON |

## Project Structure

```text
energy-adaptive-load-management-lpc2148/
│
├── docs/
│   └── Energy-Adaptive-Load-Management-Report.pdf
│
├── hardware/
│   ├── LPCBoard_Case_1.png
│   ├── LPCBoard_Case_2.png
│   ├── LPCBoard_Case_3.png
│   ├── LPCBoard_Case_4.png
│   ├── Loads_Case_1.png
│   ├── Loads_Case_2.png
│   ├── Loads_Case_3.png
│   └── Loads_Case_4.png
│
├── simulation/
│   ├── Proteus_Case_1.png
│   ├── Proteus_Case_2.png
│   ├── Proteus_Case_3.png
│   └── Proteus_Case_4.png
│
├── src/
│   └── main.c
│
├── .gitignore
└── README.md
