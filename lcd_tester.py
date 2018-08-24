"""LCD tester"""

import time
import RPi.GPIO as GPIO
import charlcd
#from charlcd import direct as lcd_direct
#from charlcd.drivers.gpio import Gpio


GPIO.setmode(GPIO.BCM)
GPIO.setup(25, GPIO.OUT)   # RS
GPIO.setup(24, GPIO.OUT)   # E
GPIO.setup(22, GPIO.OUT)  # DB4
GPIO.setup(23, GPIO.OUT)  # DB5
GPIO.setup(27, GPIO.OUT)  # DB6
GPIO.setup(17, GPIO.OUT)  # DB7

lcd = charlcd.direct.CharLCD(16, 2, Gpio())

lcd.write('BEER!')
lcd.write('More beer', 0, 1)

time.sleep(5)
#lcd.clear()

lcd.write('Exiting')
lcd.write('Now', 0, 1)
time.sleep(5)
#lcd.shutdown()

GPIO.cleanup()
