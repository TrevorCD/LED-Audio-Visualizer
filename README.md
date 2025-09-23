# Sound-Reactive-Led-Totem

![Constructed Project](images/constructed.jpg "Constructed Project")

## Description

This project uses an arduino and MAX4466 to create sound reactivity that is
outputted to LEDs. It is designed for use inside of totems for music festivals.

## Requirements

1. Arduino with at least 4000 bytes of program storage, at least 500 bytes of dynamic memory, and 5V power. (Arduino Nano used)
2. Arduino IDE and USB OR AVR programmer
3. Electronic components (see below)
4. 3D printer and chasis components (see below)
5. Soldering iron

## Usage

1. Set pins in Config section of totem.ino the output pins on your arduino that you wish to use. LED_PIN must support PWM and MIC_PIN must allow analog reads.
3. Follow circuit diagram for the most basic set up.

## Circuit

![Graphical Circuit Diagram](images/circuit_diagram.png "Graphical Circuit Diagram")

![Circuit Schematic](images/circuit_schematic.png "Circuit Schematic")

Notes:
1. The 10 ohm resistor between the positive and negative usb power must be >= 5 watts. This resistor is there to ensure the portable battery does not auto shutoff
2. The USB power icon refers to item 7 in electronic components
3. Both the USB A cable end and the Arduino need to be plugged into the portable charger
4. This circuit does not make use of the button feature
5. Depending on the LEDs you use, you may have to use different resistors. https://ledcalculator.net/ is a good resource for calculating which resistors you need.

## Electronic components

1. Arduino Nano https://www.amazon.com/dp/B0CM3C3FCZ
2. MAX4466 https://www.amazon.com/dp/B08N4FNFTR
3. INIU portable charger https://www.amazon.com/dp/B09176JCKZ
4. 10 ohm 5W resistor https://www.amazon.com/dp/B0DV3LVCJG
5. 6x 3.0~3.2V/20mA LEDs
6. 6x 100 ohm 1/4W 1% resistors
7. USB A cable (with the other end stripped)
8. 5cm x 7cm PCB Board
9. 2N2222 or any NPN Transistor

## Chasis components

1. Transparent 1.75mm PLA https://www.amazon.com/dp/B07ZNG4L9P
2. 6x M3 70mm machine screws with nuts https://www.amazon.com/dp/B07D4KLF5H
3. 6-12 foot painter pole https://www.homedepot.com/p/Wooster-6-ft-12-ft-Sherlock-Extension-Pole-00R0560000/100132422
4. All stl files in main/models/ printed (see notes)

Notes:
1. totemOrbFull.stl may be printed in two parts (totemOrbHalf*) to enable easier printing
2. Only the totemOrb needs to be printed with transparent PLA; however, all pieces can be printed with transparent PLA
