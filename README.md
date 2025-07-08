# Sound-Reactive-Led-Totem

## Description

This project uses an arduino and MAX4466 to create sound reactivity that is
outputted to LEDs. It is intended for use inside of totems for music festivals.

## Requirements

1. Arduino with at least 4000 bytes of program storage, at least 500 bytes of
dynamic memory, and 5V power.

1. MAX4466 electret microphone and amp, with the gain set to minimum.

1. Arduino-ide, arduino-cli, or programmer to upload code to arduino.

## Usage

1. Set pins in Config section of totem.ino the output pins on your arduino that
you wish to use. LED_PIN must support PWM and MIC_PIN must allow analog reads.

3. Follow circuit diagram (To be added) for the most basic set up.
