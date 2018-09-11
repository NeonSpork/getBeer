import RPi.GPIO as GPIO
from hx711 import HX711


hx = HX711(dout_pin=2, pd_sck_pin=3, gain_channel_A=64, select_channel='A')
raw = hx.get_data_mean(times=10)
print(raw)
hx.set_offset(100350, channel='A', gain_A=64)
hx.set_scale_ratio(channel='A', gain_A=64, scale_ratio=36.2109)

#inp = input('put weight on and hit enter')
#data = hx.get_data_mean(times=10)
#print(data)
#ratio = data/876
#print(ratio)

#hx.set_scale_ratio(channel='A', gain_A=64, scale_ratio=ratio)

grams = hx.get_weight_mean(times=10)
print(grams)
hx.reset()
GPIO.cleanup()

