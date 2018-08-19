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
GPIO.setup(21, GPIO.IN)  # Button
GPIO.setup(13, GPIO.IN)  # Flow meter
GPIO.setup(5, GPIO.OUT, initial=0)  # Magnetic valve, starts closed


def buttonDown():
    if GPIO.input(21):
        return True
    else:
        return False


def openValve():
    GPIO.output(5, True)


def shutValve():
    GPIO.output(5, False)


def countFlow():
    dispensedVolume = 0
    if GPIO.input(13):  # Pulse from flow meter
        dispensedVolume += 1  # Adjust this to whatever equates 1 ml
    return int(dispensedVolume)


def cleanUp():
    GPIO.cleanup()
