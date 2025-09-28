# LED Audio Visualizer
<div width="100%">
  <img align="left" src="images/constructed.jpg" width="38.197%"/>
  
  <p>
    This project uses an Arduino Nano and an MAX4466 (electret microphone amplifier) breakout board to dynamically scale LED brightness in response to sound.
    The visual output resembles pre-programmed lighting, with brightness peaks smoothly matching to the beat of music.
    <br><br>
    To achieve this, the Arduino polls the MAX4466's analog output at 100Hz (adjustable), places the amplitude samples in a circular buffer, and uses the stored values to calculate a continuous average.
    For each sample, the amplitude is compared to the running average to calculate the PWM output that drives the LEDs through an NPN transistor.
    LED brightness scales from 0 (for samples at or below half the average) to 255 (for samples at or above twice the average), with intermediate values forming a smooth gradient.
    Custom 3D printed parts are used to house the electronics and battery.
  </p>
  <br>
  See it here: <a href="https://www.youtube.com/watch?v=eAFF40k64hU" target="_blank">Youtube Demo</a>
  <br>
</div>

<br>

## Overview

### Requirements
* Arduino or most other microcontrollers
  * Low minimum specs: **4kb flash memory** and **500b RAM**
  * Must support: PWM, 2 GPIO Pins
* Arduino programming
  * ArduinoIDE
  * USB-A to USB-Mini cable
* 3D printer & slicer software
* Soldering iron
* Wire strippers / cutters
* Electronic and housing components [(see below)](#component-list)
* Music

### Usage
This technology performs best in high amplitude environments such as concerts or festivals.  

#### Config
* Set LED_PIN and MIC_PIN to appropriate digital PWM pin and analog pin on the Arduino
* Timing adjustments:
  * SAMPLE_TIME: The period in milliseconds over which amplitude is calculated. If SAMPLE_TIME = 10, sample rate = 100Hz.
  * WINDOW_SIZE: The size of the circular buffer. Larger buffers take longer to adjust to new average sound levels. 
  * RUNNING_ITERS: The number of samples taken before an inner average is added to the window. Large values allow accurate and long continuous averages in memory constrained environments. 
  * Average period (seconds) = SAMPLE_TIME * WINDOW_SIZE * RUNNING_ITERS / 1000.
* Sensitivity adjustments:
  * PEAK: The coefficient of the continuous average for the brightness ceiling. ( brightness = max IF sample ≥ continuous_average * PEAK )
  * VALLEY: The coefficient of the continous average for the brightness floor.  ( brightness = min IF sample ≤ continuous_avergae * VALLEY )

> [!TIP]
> MAX4466 Amplitude is adjustable. This project is designed for high amplitude environemnts; subsequently, the MAX4466 amplification was set to minimum for calibration.  

<br>

## Component List

### Electronic Components
1. 1x [Arduino Nano (ATMega328)](https://www.amazon.com/dp/B0CM3C3FCZ) <sub><sup>(or any comprable MCU)</sup></sub>
2. 1x [MAX4466 (electret Bare Wire]phone and amp)](https://www.amazon.com/dp/B08N4FNFTR)
3. 1x [INIU portable charger](https://www.amazon.com/dp/B09176JCKZ)
4. 2x [10Ω 5W resistor](https://www.amazon.com/dp/B0DV3LVCJG)
5. 6x 3.0~3.2V/20mA LEDs
6. 6x 100Ω 1/4W 1% resistors
7. 1x Cable A: 12+ inch USB-A cable (other end does not matter)
8. 1x Cable B: 10+ inch USB-Mini to USB-A cable (separate from Arduino programming cable)
9. 1x 5cm x 7cm (solderable) through hole PCB
10. 1x 2N2222: NPN bipolar junction transistor
11. 3x solderable breadboard wires (≥6")

### Housing Components
1. [Transparent 1.75mm PLA](https://www.amazon.com/dp/B07ZNG4L9P) <sub><sup>(usage of other PLA is optional)</sup></sub>
2. [7x M3 70mm machine screws with nuts](https://www.amazon.com/dp/B07D4KLF5H)
3. [6-12 foot painter pole](https://www.homedepot.com/p/Wooster-6-ft-12-ft-Sherlock-Extension-Pole-00R0560000/100132422)
4. Super glue

### 3D Printed Components
1. With *any* PLA:
   * totemBaseBottom.stl
   * totemBaseMiddle.stl
   * totemBaseTop.stl
2. With **transparent** PLA:
   * totemOrbFull.stl **- OR -** *both* totemOrbHalfBottom.stl *and* totemOrbHalfTop.stl <sub><sup>(with transparent PLA)</sup></sub>

<br>

## How to Build

### Instructions

#### I - Start Assembly
1. Using the USB-A to Mini cable mentioned in the [Requirements](#requirements), connect the Arduino to your personal computer. Using ArduinoIDE, flash the Arduino with totem.ino. 
2. 3D print all the necessary components. The totemBaseBottom, totemBaseMiddle, and totemBaseTop pieces do not need supports.
   * For printing the orb in one piece: Use supports on the inside of totemOrbFull, supporting the center.
   * For printing the orb in two pieces: Use supports on totemOrbHalfTop. Superglue the orb halves together once printed.

#### II - Cable Setup
***For Cable Setup 1-6, refer to the [Cable Rerefence](#cable-reference-table) below.***
1. Cut Cable A such that there is 5 inches of length off of the USB-A end. On the other end, cut the connector off and leave at least 7 inches of length.
2. Similarly, cut Cable B such that there is 5 inches of length off the USB-A end, and 5 inches of length off the USB-Mini end.
3. On all 3 cable remenants with ports, strip the wire on the non-port end to expose 1.5 inches of the internal red and black wires. Do this to both sides of the Cable A half that does not have a port attached.
4. Strip 0.5 inches off of each of the red and black wire end to expose the copper. This should be 10 copper wires in total.
5. Wrap both halves of Cable B's exposed wire on each side of a 10Ω 5W resistor such that both red wires in Cable B are on the same side of the resistor, and both black on the other.
6. Similarly, do this with the ends of both halves of Cable A on the other 10Ω 5W resistor.

### III - Wiring & Soldering
***For the Soldering 1-4, refer to the [Schematics](#circuit-diagrams) for all wiring and soldering.***
1. Solder the 10Ω 5W resistor to the copper wire in the usb lines. You now have reconstructed Cable A and Cable B, but with a 10Ω 5W resistor in the line.
2. Solder the Arduino, LEDs, 2N2222, and resistors to the PCB Board.
3. Solder the red exposed wire of Cable A to the LEDs, and the black exposed wire to the 2N2222's emitter.
4. For the connections between the Arduino and MAX4466, solder the breadboard wires to their respective pins and the MAX4466 breakout board.

### IV - Mount Electronics
1. Feed the MAX4466 through totemBaseTop, between the outer wall and running supports, on the side with 2 screw holes.
2. Super glue the MAX4466 to the inside of totemBaseMiddle, with the Bare Wire]phone part of the component inside the hole in the side.
3. Once the MAX4466 is secure, slot the INIU portable charger inside totemBaseMiddle, with the ports accessible through the side cutout.
4. Slot the PCB onto the pegs on the running supports of totemBaseTop. You may want to use super glue to secure the PCB to totemBaseTop.
5. Plug Cable B into the Arduino's USB-Mini port, and feed the cable through the cutout along the top of totemBaseTop.

### V - Final Assembly
1. Slide totemBaseBottom onto the end of the painter's pole so that the holes line up. Slide one of the M3 70mm machine screws through the holes and secure with the nut.
2. Insert the remaining three machine screws through the housing via the opening on totemBaseBottom, through all three totem base components.
3. Set the totem orb on top of the base components, aligning it's screw holes with the base pieces'.
4. Secure the whole housing together by screwing the nuts onto the ends of the machine screws.

<br>

### Cable Reference Table

#### Unmodified cables

```
A                                                                                          [USB-Mini]-[10" Jacket]-[USB-A]
```
```
B                                                                                          [Any USB ]-[12" Jacket]-[USB-A]
```

#### Cable step 2: Both cables cut into separate ends, non USB-A connector cut off of cable A

```
A                                                                                                      [USB-A]-[5" Jacket]
.                                                                                                              [7" Jacket]
```
```
B                                                                                                   [USB-Mini]-[5" Jacket]
.                                                                                                      [USB-A]-[5" Jacket]
```

#### Cable step 4: Cable jacket stripped to red and black signal wires, signal wires stripped to bare copper

```
A                                                                 [USB-A]-[3.5" Jacket]-[1" Signal Wires]-[0.5" Bare Wire]
.                                        [0.5" Bare Wire]-[1" Signal Wires]-[4" Jacket]-[1" Signal Wires]-[0.5" Bare Wire]
```
```
B                                                              [USB-Mini]-[3.5" Jacket]-[1" Signal Wires]-[0.5" Bare Wire]
.                                                                 [USB-A]-[3.5" Jacket]-[1" Signal Wires]-[0.5" Bare Wire]
```

#### Cable Step 6: Final cable configuration with 10Ω 5W resistors

```
A        [0.5" Bare Wire]-[1" Signal Wires]-[4" Jacket]-[1" Signal Wires]-[Resist]-[1" Signal Wires]-[3.5" Jacket]-[USB-A]
```
```
B                              [USB-Mini]-[3.5" Jacket]-[1" Signal Wires]-[Resist]-[1" Signal Wires]-[3.5" Jacket]-[USB-A]
```

<br>

### Circuit Diagrams

<table width="100%">
  <tr>
    <td align="center" width="51%">
      <img width="100%" src="images/circuit_schematic.png"/><br/>
      - Schematic Diagram -
      <br><br><sub><sup> </sup></sub>
    </td>
    <td align="center" width="48.5%">
      <img width="100%" src="images/circuit_diagram.png"/><br/>
      - Pictoral Diagram -
      <br><sub><sup>(see notes)</sup></sub>
    </td>
  </tr>
</table>

> [!WARNING]
> The 10Ω resistor between the positive and negative USB wires ***must be ≥ 5 watts*** or you risk the resistor **exploding** or **catching fire**.  
> ***ALSO***, you need **10Ω 5W resistors** in **BOTH** the USB cable powering the Arduino, **AND** the USB cable powering the LEDs.  

> [!NOTE]
> The Pictoral Circuit Diagram is missing key information:  
> - The USB power icon refers to Cable A and The Arduino needs to be plugged into the INIU portable via Cable B. See items 7, 3, 8 in [Electronic Components](#electronic-components).  
> - Both the USB cable to the Arduino and transistor need to have a 10Ω 5W resistor to prevent the INIU battery from performing automatic shutoff.  

> [!TIP]
> Depending on the number and specs of the LEDs you use, you will likey have to use different resistors. You can use [this website](https://ledcalculator.net/) to calculate which resistors you need.  
