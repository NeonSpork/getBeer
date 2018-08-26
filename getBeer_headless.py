"""getBeer_headless

This version of the automatic dispensor only uses a small LCD
screen and a physical button. The primary objective is to
run the Pi zero and solenoid from batteries, so that this unit
can be mobile, aka portable beer dispensor!

Wiring the hardware:
Button          - GP21 (pin 40) & GND (pin 39)
Magnetic valve  - GP5 (pin 29) & GND (pin 30), both via relay to battery/valve

See lcd.py for wiring the 16x2 LCD display.
"""

import sys
import RPi.GPIO as GPIO
import lcd


class BeerDispenser(object):
    def __init__(self):
        super(BeerDispenser, self).__init__()

        # Sets numeration of channels according to pin numbers on Pi
        GPIO.setwarnings(False)
        GPIO.setmode(GPIO.BCM)

        # Set up GPIO pins
        GPIO.setup(21, GPIO.IN, pull_up_down=GPIO.PUD_UP)  # Button
        GPIO.setup(5, GPIO.OUT, initial=0)  # Magnetic valve, starts closed

        GPIO.add_event_detect(21, GPIO.BOTH, callback=self.buttonSignal)

        # Initializing 16x2 lcd screen
        lcd.lcd_init()
        lcd.lcd_clear()

        # Parameters for dispenser
        self.buttonDown = False

    def openValve(self):
        GPIO.output(5, True)

    def shutValve(self):
        GPIO.output(5, False)

    def buttonSignal(self, channel):
        if GPIO.input(21):
            self.buttonDown = False
        else:
            self.buttonDown = True
        return self.buttonDown

    def buttonCheck(self):
        if self.buttonDown:
            self.openValve()
            lcd.lcd_string('Dispensing BEER!', 1)
            lcd.lcd_string('Enjoy your drink', 2)
        else:
            self.shutValve()
            lcd.lcd_string('READY: Push', 1)
            lcd.lcd_string('button for beer!', 2)

if __name__ == '__main__':
    b = BeerDispenser()
    while True:
        try:
            b.buttonCheck()
        except KeyboardInterrupt:
            lcd.lcd_string('Clean exit', 1)
            lcd.lcd_string('Shutting down', 2)
            GPIO.cleanup()
            print("Clean exit.")
            sys.exit()
