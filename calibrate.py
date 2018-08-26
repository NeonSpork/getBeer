"""Calibrate

Small program to print output of load sensor to calibrate
and calculate ratio (scale) to get HX711 to work in grams

Wiring:
Load sensor - VCC=3v3 (pin 1), GND (pin 9), DT=GP2 (pin 3), SCK=GP3 (pin 5)
"""

import RPi.GPIO as GPIO
from hx711 import HX711

print("Scale initializing...")
hx = HX711(2, 3)
print("Ready.\n")

# First place nothing on scale
zero = hx.read_average()
print("Value of zero scale is: {}".format(zero))
print("{} should be entered as self.OFFSET in hx711.py, line 37\n".format(zero))

# Place something which the exact weight is known on the scale
print("Place an object with a known weight on the scale.")
input("Press ENTER to continue.")
knownWeight = hx.read_average() - zero
isInt = False
while not isInt:
    gramWeight = input("Enter weight of object in grams: ")
    if gramWeight is int:
        ratio = knownWeight/gramWeight
        isInt = True
    else:
        print("Please enter a valid integer.")
        isInt = False
print("Ratio: {}/{} = {}".format(knownWeight, gramWeight, ratio))
print("{} shoud be entered as self.SCALE in hx711.py, line 38\n")
print("Calibration program complete, exiting.")
hx.power_down()
GPIO.cleanup()
