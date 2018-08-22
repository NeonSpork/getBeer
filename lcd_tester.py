"""LCD tester"""

import time
import RPi.GPIO as GPIO
from charlcd import direct as lcd_direct
from charlcd.drivers.gpio import Gpio

GPIO.setmode(GPIO.BOARD)

lcd = lcd_direct.CharLCD(16, 2, Gpio())

g = Gpio()
g.pins = {
    'RS': 26,
    'E': 24,
    'DB4': 22,
    'DB5': 18,
    'DB6': 16,
    'DB7': 12
}

l = lcd.CharLCD(16, 2, g, cursor_visible=0)

l.write('BEER!!\nMore BEER!!')

time.sleep(5)

l.write('Exiting')

time.sleep(5)
l.shutdown()

GPIO.cleanup()
