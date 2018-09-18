"""getBeer

Control unit for beer dispensor built into kegerator.

Wiring the hardware:
Magnetic valve  - GP5 (pin 29) & GND (pin 30)
Temperature - GP4 (pin 7), GND (pin 20) & 3v3 (pin 1)
Load sensor - VCC=3v3 (pin 17), GND (pin 9), DT=GP2 (pin 3), SCK=GP3 (pin 5)
See LCD for wiring 16x2 display
"""

import sys
import pygame as pg
from multiprocessing import Process
from settings import *
import RPi.GPIO as GPIO
from hx711 import HX711
from w1thermsensor import W1ThermSensor
import lcd


GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)


class BeerDispenser(object):
    def __init__(self):
        super(BeerDispenser, self).__init__()
        pg.init()
        self.screen = pg.display.set_mode((SWIDTH, SHEIGHT), pg.FULLSCREEN)
        pg.mouse.set_visible(True)  # change to False when using touch screen
        self.clock = pg.time.Clock()

        # Set up GPIO pins
        GPIO.setup(5, GPIO.OUT, initial=0)  # Magnetic valve, starts closed
        GPIO.setup(4, GPIO.IN)  # Temperature probe DS18S20
        GPIO.setup(2, GPIO.IN)  # Load sensor DT
        GPIO.setup(3, GPIO.OUT)  # Load sensor SCK

        # LCD
        lcd.lcd_init()
        lcd.lcd_clear()

        # Load sensor
        self.hx = HX711(dout_pin=2, pd_sck_pin=3, gain_channel_A=64, select_channel='A')
        self.hx.set_offset(100350, channel='A', gain_A=64)  # This gets calibrated to zero the sensor
        self.hx.set_scale_ratio(channel='A', gain_A=64, scale_ratio=36.2109)

        # Parameters for dispenser
        self.running = True
        self.dispensing = False
        self.buttonDown = False
        self.bg_image = 0
        self.dispenserDisplay = True
        self.beerChooser = False
        self.tempSensor = W1ThermSensor()
        self.counter = 0
        self.pintsLeft = 0

    def drawToScreen(self, image, x, y):
        self.image = image
        image_rect = image.get_rect()
        image_rect.center = (x, y)
        self.screen.blit(image, image_rect)

    def dispensorEvents(self):
        self.mouse = pg.mouse.get_pos()
        self.click = pg.mouse.get_pressed()
        self.keys = pg.key.get_pressed()
        if self.click[0] == 1:
            if self.mouse[0] > (SWIDTH-(200*RELX)) and self.mouse[1] > (SHEIGHT-(200*RELY)):
                self.openValve()
            if self.mouse[0] < (50*RELX) and self.mouse[1] < (50*RELY):
                self.dispenserDisplay = False
                self.beerChooser = True
                pg.time.delay(100)
            if self.mouse[0] > (SWIDTH-(50*RELX)) and self.mouse[1] < (50*RELY):
                self.running = False
        else:
            self.shutValve()
        for event in pg.event.get():
            if event.type == pg.QUIT:
                self.running = False
            if event.type == pg.KEYDOWN and event.key == pg.K_ESCAPE:
                self.running = False

    def openValve(self):
        GPIO.output(5, True)
        self.dispensing = True

    def shutValve(self):
        GPIO.output(5, False)
        self.dispensing = False

    def dispensorDraw(self):
        try:
            self.drawToScreen(BACKGROUNDS[self.bg_image], SWIDTH/2, SHEIGHT/2)
        except IndexError:
            self.drawToScreen(DEFAULT_BACKGROUND, SWIDTH/2, SHEIGHT/2)
        if self.dispensing:
            self.drawToScreen(BUTTON_ON, SWIDTH-(100*RELX), SHEIGHT-(100*RELY))
        if not self.dispensing:
            self.drawToScreen(BUTTON, SWIDTH-(100*RELX), SHEIGHT-(100*RELY))
        self.drawToScreen(PINTS_ICON, (SWIDTH*0.1), (SHEIGHT*0.9))
        if int(self.pintsLeft) <= 9:
            self.drawToScreen(NEON_NUMBER[int(str(self.pintsLeft))], (SWIDTH*0.28), (SHEIGHT*0.9))
        if int(self.pintsLeft) > 9:
            self.drawToScreen(NEON_NUMBER[int(str(self.pintsLeft)[0:1])], ((SWIDTH*0.28)-(30*RELX)), (SHEIGHT*0.9))
            self.drawToScreen(NEON_NUMBER[int(str(self.pintsLeft)[1:2])], ((SWIDTH*0.28)+(30*RELX)), (SHEIGHT*0.9))
        self.drawToScreen(QUIT, (25*RELX), (25*RELY))
        pg.display.flip()

    def beerChooserEvents(self):
        self.mouse = pg.mouse.get_pos()
        self.click = pg.mouse.get_pressed()
        self.keys = pg.key.get_pressed()
        x, y = SWIDTH/2, SHEIGHT/2
        if self.click[0] == 1:
            if self.mouse[0] < (50*RELX) and self.mouse[1] < (50*RELY):
                self.dispenserDisplay = True
                self.beerChooser = False
                pg.time.delay(100)
            if (x-(150*RELX)) < self.mouse[0] < (x+(150*RELX)) and self.mouse[1] < (150*RELY):
                self.bg_image = 0  # Default background
                self.dispenserDisplay = True
                self.beerChooser = False
                pg.time.delay(100)
            if (x-(300*RELX)) < self.mouse[0] < (x-(150*RELX)) and (150*RELY) < self.mouse[1] < (300*RELY):
                self.bg_image = 1
                self.dispenserDisplay = True
                self.beerChooser = False
                pg.time.delay(100)
            if (x-(150*RELX)) < self.mouse[0] < x and (150*RELY) < self.mouse[1] < (300*RELY):
                self.bg_image = 2
                self.dispenserDisplay = True
                self.beerChooser = False
                pg.time.delay(100)
            if x < self.mouse[0] < (x+(150*RELX)) and (150*RELY) < self.mouse[1] < (300*RELY):
                self.bg_image = 3
                self.dispenserDisplay = True
                self.beerChooser = False
                pg.time.delay(100)
            if (x+(150*RELX)) < self.mouse[0] < (x+(300*RELX)) and (150*RELY) < self.mouse[1] < (300*RELY):
                self.bg_image = 4
                self.dispenserDisplay = True
                self.beerChooser = False
                pg.time.delay(100)
            if (x-(300*RELX)) < self.mouse[0] < (x-(150*RELX)) and (300*RELY) < self.mouse[1] < (450*RELY):
                self.bg_image = 5
                self.dispenserDisplay = True
                self.beerChooser = False
                pg.time.delay(100)
            if (x-(150*RELX)) < self.mouse[0] < x and (300*RELY) < self.mouse[1] < (450*RELY):
                self.bg_image = 6
                self.dispenserDisplay = True
                self.beerChooser = False
                pg.time.delay(100)
            if x < self.mouse[0] < (x+(150*RELX)) and (300*RELY) < self.mouse[1] < (450*RELY):
                self.bg_image = 7
                self.dispenserDisplay = True
                self.beerChooser = False
                pg.time.delay(100)
            if (x+(150*RELX)) < self.mouse[0] < (x+(300*RELX)) and (300*RELY) < self.mouse[1] < (450*RELY):
                self.bg_image = 8
                self.dispenserDisplay = True
                self.beerChooser = False
                pg.time.delay(100)
            if (x-(300*RELX)) < self.mouse[0] < (x-(150*RELX)) and (450*RELY) < self.mouse[1] < (600*RELY):
                self.bg_image = 9
                self.dispenserDisplay = True
                self.beerChooser = False
                pg.time.delay(100)
            if (x-(150*RELX)) < self.mouse[0] < x and (450*RELY) < self.mouse[1] < (600*RELY):
                self.bg_image = 10
                self.dispenserDisplay = True
                self.beerChooser = False
                pg.time.delay(100)
            if x < self.mouse[0] < (x+(150*RELX)) and (450*RELY) < self.mouse[1] < (600*RELY):
                self.bg_image = 11
                self.dispenserDisplay = True
                self.beerChooser = False
                pg.time.delay(100)
            if (x+(150*RELX)) < self.mouse[0] < (x+(300*RELX)) and (450*RELY) < self.mouse[1] < (600*RELY):
                self.bg_image = 12
                self.dispenserDisplay = True
                self.beerChooser = False
                pg.time.delay(100)
        for event in pg.event.get():
            if event.type == pg.QUIT:
                self.running = False
            if event.type == pg.KEYDOWN and event.key == pg.K_ESCAPE:
                self.running = False

    def beerChooserDraw(self):
        self.drawToScreen(BRICKS, SWIDTH/2, SHEIGHT/2)
        self.drawToScreen(DEFAULT_THUMBNAIL, SWIDTH/2, (75*RELY))
        thumbImage = 1
        x = (SWIDTH/2)-(225*RELX)
        y = (225*RELY)
        for iy in range(3):
            for ix in range(4):
                try:
                    self.drawToScreen(THUMB[thumbImage], x, y)
                except IndexError:
                    self.drawToScreen(COMING_SOON, x, y)
                x += (149*RELX)
                thumbImage += 1
            y += (149*RELY)
            x = (SWIDTH/2)-(225*RELX)
        self.drawToScreen(QUIT, (25*RELX), (25*RELY))
        pg.display.flip()

    def kegVolume(self):
        dryKegVolume = 0  # Dry weight of keg system
        wetKegVolume = self.hx.get_weight_mean(times=1) - dryKegVolume
        if wetKegVolume < 0:
            wetKegVolume = 0
        return wetKegVolume

    def pintsCalculation(self):
        self.pintsLeft = int(self.kegVolume()/500)

    def kegTemp(self):
        kegTemperature = self.tempSensor.get_temperature()
        return kegTemperature

    def run(self):
        self.clock.tick(FPS)
        if self.dispenserDisplay:
            self.dispensorEvents()
            self.dispensorDraw()
        if self.beerChooser:
            self.beerChooserEvents()
            self.beerChooserDraw()
        self.counter += 1
        if self.counter > 60:
            self.pintsCalculation()
            self.counter = 0

    def infoDisplay(self):
        while self.running:
            try:
                lcd.lcd_string('{} ml'.format(int(self.kegVolume())), 1)
                lcd.lcd_string('{} Celcius'.format(self.kegTemp()), 2)
            except KeyboardInterrupt:
                self.running = False

    def mainLoop(self):
        while self.running:
            try:
                self.run()
            except KeyboardInterrupt:
                self.running = False
        else:
            GPIO.cleanup()
            pg.quit()
            sys.exit()


if __name__ == '__main__':
    b = BeerDispenser()
    b.pintsCalculation()
    littleLCD = Process(target=b.infoDisplay)
    gameLoop = Process(target=b.mainLoop)
    littleLCD.start()
    gameLoop.start()
    try:
        while b.running:
            try:
                littleLCD.join()
                gameLoop.join()
            except KeyboardInterrupt:
                b.running = False
    finally:
        b.hx.power_down()
        littleLCD.join()
        gameLoop.join()
        lcd.lcd_clear()
        pg.quit()
        GPIO.cleanup()
        sys.exit()
