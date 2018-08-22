"""LCD tester"""

import time
import RPi.GPIO as GPIO
from charlcd import direct as lcd_direct
from charlcd.drivers.gpio import Gpio


GPIO.setmode(GPIO.BCM)

l = lcd_direct.CharLCD(16, 2, cursor_visible=0)

l.write('BEER!!\nMore BEER!!')

time.sleep(5)

l.write('Exiting')

time.sleep(5)
l.shutdown()

GPIO.cleanup()
