"""weigh dry keg

Small program to get dry weight of keg
Value should be entered as dryKegVolume in getBeer_touch.py, line 79
This program should only be run AFTER calibrating scale.
"""

import RPi.GPIO as GPIO
from hx711 import HX711


print("Scale initializing...")
hx = HX711(dout_pin=2, pd_sck_pin=3, gain_channel_A=64, select_channel='A')
hx.set_offset(100350, channel='A', gain_A=64)
hx.set_scale_ratio(channel='A', gain_A=64, scale_ratio=36.2109)
print("Ready.\n")
dryWeight = hx.get_weight_mean(times=10)
print("Average dry weight of keg is {} grams".format(dryWeight))
hx.reset()
GPIO.cleanup()
