"""LED display code

16x2 LED display, initialize and control display.
Code piggybacked off Matt Hawkins who wrote almost all of the following script.
https://www.raspberrypi-spy.co.uk/2012/07/16x2-lcd-module-control-using-python/

######## How to wire the LCD screen ########
## Pin on LCD #############|## Pin on RPi ##
1    VSS                     =  6   GND
2    VDD                     =  2   5V
3    V0 (Contrast 0V-5V)     =  6   GND via 10k potentiometer
4    RS (Register Select)    =  22  GP25
5    R/W (Read Write)        =  6   GND
6    E (Enable or Strobe)    =  18  GP24
7    D0 (Data bit 0)         =  //  UNUSED
8    D1 (Data bit 1)         =  //  UNUSED
9    D2 (Data bit 2)         =  //  UNUSED
10   D3 (Data bit 3)         =  //  UNUSED
11   D4 (Data bit 4)         =  15  GP22
12   D5 (Data bit 5)         =  16  GP23
13   D6 (Data bit 6)         =  13  GP27
14   D7 (Data bit 7)         =  11  GP17
15   A (LCD Backlight +5V**) =  2   5V (with resistor? or use 3.3V?)
16   K (LCD Backlight GND)   =  6   GND
"""

import RPi.GPIO as GPIO
import time

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(25, GPIO.OUT)   # RS
GPIO.setup(24, GPIO.OUT)   # E
GPIO.setup(22, GPIO.OUT)  # DB4
GPIO.setup(23, GPIO.OUT)  # DB5
GPIO.setup(27, GPIO.OUT)  # DB6
GPIO.setup(17, GPIO.OUT)  # DB7

# Define GPIO to LCD mapping
LCD_RS = 25
LCD_E = 24
LCD_D4 = 22
LCD_D5 = 23
LCD_D6 = 27
LCD_D7 = 17

# Define device constants
LCD_WIDTH = 16
LCD_LINE_1 = 0x80  # LCD RAM address for first line
LCD_LINE_2 = 0xC0  # LCD RAM address for second line

LCD_CHR = True     # Flag true to send character bit
LCD_CMD = False    # Flag false to send command bit

# Timing delays
E_PULSE = 0.0005
E_DELAY = 0.0005


def lcd_init():
    # Initialize LCD display
    lcd_byte(0x33, LCD_CMD)  # 110011 Initialise
    lcd_byte(0x32, LCD_CMD)  # 110010 Initialise
    lcd_byte(0x06, LCD_CMD)  # 000110 Cursor move direction
    lcd_byte(0x0C, LCD_CMD)  # 001100 Display On,Cursor Off, Blink Off
    lcd_byte(0x28, LCD_CMD)  # 101000 Data length, number of lines, font size
    lcd_byte(0x01, LCD_CMD)  # 000001 Clear display
    time.sleep(E_DELAY)


def lcd_byte(bits, mode):
    # Send byte to data pins
    # bits = data
    # mode = True  for character
    #        False for command

    GPIO.output(LCD_RS, mode)  # RS

    # High bits
    GPIO.output(LCD_D4, False)
    GPIO.output(LCD_D5, False)
    GPIO.output(LCD_D6, False)
    GPIO.output(LCD_D7, False)
    if bits & 0x10 == 0x10:
        GPIO.output(LCD_D4, True)
    if bits & 0x20 == 0x20:
        GPIO.output(LCD_D5, True)
    if bits & 0x40 == 0x40:
        GPIO.output(LCD_D6, True)
    if bits & 0x80 == 0x80:
        GPIO.output(LCD_D7, True)

    # Toggle 'Enable' pin
    lcd_toggle_enable()

    # Low bits
    GPIO.output(LCD_D4, False)
    GPIO.output(LCD_D5, False)
    GPIO.output(LCD_D6, False)
    GPIO.output(LCD_D7, False)
    if bits & 0x01 == 0x01:
        GPIO.output(LCD_D4, True)
    if bits & 0x02 == 0x02:
        GPIO.output(LCD_D5, True)
    if bits & 0x04 == 0x04:
        GPIO.output(LCD_D6, True)
    if bits & 0x08 == 0x08:
        GPIO.output(LCD_D7, True)

    # Toggle 'Enable' pin
    lcd_toggle_enable()


def lcd_toggle_enable():
    # Toggle enable
    time.sleep(E_DELAY)
    GPIO.output(LCD_E, True)
    time.sleep(E_PULSE)
    GPIO.output(LCD_E, False)
    time.sleep(E_DELAY)


def lcd_clear():
    lcd_byte(0x01, LCD_CMD)


def lcd_string(message, line):
    # Send string to display
    message = message.ljust(LCD_WIDTH, " ")
    if line == 1:
        lcd_byte(LCD_LINE_1, LCD_CMD)

        for i in range(LCD_WIDTH):
            lcd_byte(ord(message[i]), LCD_CHR)
    if line == 2:
        lcd_byte(LCD_LINE_2, LCD_CMD)

        for i in range(LCD_WIDTH):
            lcd_byte(ord(message[i]), LCD_CHR)
