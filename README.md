

# Stop Watch
This repository contains the implementation of a Stop Watch system using the ATmega32 microcontroller. The system uses a 1MHz clock frequency, Timer1 configured in CTC mode to count the stopwatch time, and six common anode 7-segments connected using the multiplexed technique. Additionally, the system supports external interrupts for resetting, pausing, and resuming the stopwatch using push buttons.

## Introduction
The Stop Watch system is a precise and reliable timekeeping device built around the ATmega32 microcontroller. By utilizing Timer1 in CTC (Clear Timer on Compare Match) mode, it ensures accurate time measurement. The time is displayed on six common anode 7-segment displays, which are controlled using a multiplexing technique. 

To enhance user interaction, the system includes three external interrupts:

• INT0 (Reset): Triggered by a push button with an internal pull-up resistor, resetting the stopwatch when a falling edge is detected.

•INT1 (Pause): Triggered by a push button with an external pull-down resistor, pausing the stopwatch when a rising edge is detected.

•INT2 (Resume): Triggered by a push button with an internal pull-up resistor, resuming the stopwatch when a falling edge is detected.

## Hardware Requirements

• ATmega32 Microcontroller

• 6 x Common Anode 7-segment displays

• 1 x 7447 Decoder

• Resistors (appropriate values for 7-segment current limiting and BJT base current limiting)

• Push buttons

• Resistors for pull-up and pull-down configurations

• Breadboard or PCB for assembly

• Connecting wires
## Schematic
![Schematic](https://github.com/Malak-Nabil/Stop-Watch/assets/112269807/00d3dc0e-49b2-46b3-a8e8-2de803606356)

## Setting Up the Simulation

• Open Proteus: Launch the Proteus design software.

• Load Project: Open the project_proteus_simulation.pdsprj file from the repository.

• Run Simulation: Start the simulation to see the Stop Watch in action.

• Interact: Use the push buttons in the simulation to reset, pause, and resume the stopwatch.
