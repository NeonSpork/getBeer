"""Dispenser module.

Initializations and control of GPIO pins on raspberry pi.
This is where the actual hardware interfaces with the program.

Wiring the hardware:
Button          - GP21 (pin 40] & GND (pin 39)
Flow meter      - GP13 (pin 33) & GND (pin 34)
Magnetic valve  - GP5 (pin 29) & GND (pin 30)
"""

import RPi.GPIO as GPIO

# Sets numeration of channels according to pin numbers on Pi
GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)

# Set up GPIO pins
GPIO.setup(40, GPIO.IN)  # Button
GPIO.setup(33, GPIO.IN)  # Flow meter
GPIO.setup(29, GPIO.OUT, initial=0)  # Magnetic valve, starts closed


def buttonDown():
    if GPIO.input(40):
        return True


def openValve():
    GPIO.output(29, True)


def shutValve():
    GPIO.output(29, False)


def countFlow():
    dispensedVolume = 0
    if GPIO.input(33):  # Pulse from flow meter
        dispensedVolume += 1  # Adjust this to whatever equates 1 ml
    return int(dispensedVolume)


def cleanUp():
    GPIO.cleanup()
