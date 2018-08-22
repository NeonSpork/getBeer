"""LCD tester"""

import time
import Adafruit_CharLCD as LCD
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BOARD)

lcd_rs        = 26  # Note this might need to be changed to 21 for older revision Pi's.
lcd_en        = 24
lcd_d4        = 22
lcd_d5        = 18
lcd_d6        = 16
lcd_d7        = 12
lcd_backlight = 4

lcd_columns = 16
lcd_rows = 2

lcd = LCD.Adafruit_CharLCD(lcd_rs,
                           lcd_en,
                           lcd_d4,
                           lcd_d5,
                           lcd_d6,
                           lcd_d7,
                           lcd_columns,
                           lcd_rows,
                           lcd_backlight)

lcd.message('BEER!!\nMore BEER!!')

time.sleep(5)

lcd.clear()
lcd.message('Exiting')

time.sleep(5)
lcd.clear()

GPIO.cleanup()
