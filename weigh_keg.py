"""weigh dry keg

Small program to get dry weight of keg
Value should be entered as dryKegVolume in getBeer_touch.py, line 79
This program should only be run AFTER calibrating scale.
"""

import RPi.GPIO as GPIO
from hx711 import HX711


print("Scale initializing...")
hx = HX711(2, 3)
print("Ready.\n")
dryWeight = hx.get_grams()
print("Dry weight of keg is {} grams".format(dryWeight))
GPIO.cleanup()
