# Stopwatch_system
# Description
This project implements a Stop Watch system using an ATmega32 Microcontroller with the following specifications:

Microcontroller: ATmega32 with a 1 MHz clock frequency.

Timer Configuration: Timer1 is configured in CTC (Clear Timer on Compare Match) mode to count the Stop Watch time.

Display: Six Common Anode 7-segment displays are multiplexed using a 7447 decoder and NPN BJT transistors.

Start: The Stop Watch counting starts automatically when power is connected to the MCU.

Reset: External Interrupt INT0, triggered by a falling edge, is used to reset the Stop Watch time.

Pause: External Interrupt INT1, triggered by a rising edge, is used to pause the Stop Watch.

Resume: External Interrupt INT2, triggered by a falling edge, is used to resume the Stop Watch.
# Hardware Setup
Components Required:

ATmega32 Microcontroller

Six Common Anode 7-segment Displays

7447 Decoder

Push Buttons (for Reset, Pause,and Resume)

Resistors and Capacitors (as required)

Breadboard or PCB for Circuit Assembly

Power Supply (5V)
# Wiring Instructions:
Connect the ATmega32 pins according to your schematic.

Wire the six 7-segment displays using multiplexing technique as shown in the schematic.

Connect the 7447 decoder to the first four pins of PORTC.

Use the first six pins of PORTA for enabling/disabling the six 7-segment displays.

Configure external interrupts INT0, INT1, and INT2 as described in the project specifications.

Use push buttons  for time adjustment.
# Development Environment and Code
Development Environment: This project was developed using the Eclipse IDE. The AVR Eclipse Plugin was utilized to write, compile, and upload code to the ATmega32 microcontroller. The code can be found in the 'src' directory.
# Simulation
The project was tested and simulated using Proteus Design Suite. The simulation allowed for a comprehensive evaluation of the circuit and code behavior before deploying it on the hardware.

# Usage
Connect the hardware components according to the wiring instructions.

Power up the system.

The Stop Watch will start counting as soon as power is connected.

Use the external push buttons as follows:

INT0 (Falling Edge): Reset the Stop Watch time.

INT1 (Rising Edge): Pause the Stop Watch.

INT2 (Falling Edge): Resume the Stop Watch.
