"""LCD tester"""

import time
import RPi.GPIO as GPIO
from charlcd import direct as lcd_direct
from charlcd.drivers.gpio import Gpio


GPIO.setmode(GPIO.BCM)
GPIO.setup(25, GPIO.OUT)   # RS
GPIO.setup(24, GPIO.OUT)   # E
GPIO.setup(22, GPIO.OUT)  # DB4
GPIO.setup(23, GPIO.OUT)  # DB5
GPIO.setup(27, GPIO.OUT)  # DB6
GPIO.setup(17, GPIO.OUT)  # DB7

l = lcd_direct.CharLCD(16, 2, Gpio(), cursor_visible=0)

l.write('BEER!!\nMore BEER!!')

time.sleep(5)

l.write('Exiting')

time.sleep(5)
l.shutdown()

GPIO.cleanup()
