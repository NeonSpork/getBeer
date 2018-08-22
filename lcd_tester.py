"""LCD tester"""

import time
import RPi.GPIO as GPIO
from RPLCD import CharLCD


GPIO.setmode(GPIO.BCM)
GPIO.setup(25, GPIO.OUT)   # RS
GPIO.setup(24, GPIO.OUT)   # E
GPIO.setup(22, GPIO.OUT)  # DB4
GPIO.setup(23, GPIO.OUT)  # DB5
GPIO.setup(27, GPIO.OUT)  # DB6
GPIO.setup(17, GPIO.OUT)  # DB7

lcd = CharLCD(pin_rs=25,
              pin_e=24,
              pins_data=[22, 23, 27, 17],
              numbering_mode=GPIO.BCM,
              cols=16, rows=2)

lcd.write_string('BEER!!\nMore BEER!!')
lcd.clear()
time.sleep(5)

lcd.write_string('Exiting')
lcd.clear()

GPIO.cleanup()
