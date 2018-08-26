"""getBeer_touch

This version of the dispensor uses a 7 inch touch screen
as the primary interface. This is designed to be build into
a kegerator, and as such it has more permanent features like
an automatic measurement of remaining volume via a load sensor
(weight scale), temperature monitor, etc.

Wiring the hardware:
Button          - GP21 (pin 40) & GND (pin 39)
Magnetic valve  - GP5 (pin 29) & GND (pin 30)
Temperature - GP10 (pin 19), GND (pin 20) & 3v3 (pin 17)
Load sensor - VCC=3v3 (pin 1), GND (pin 9), DT=GP2 (pin 3), SCK=GP3 (pin 5)
"""

import pygame as pg
from settings import *
import RPi.GPIO as GPIO
from hx711 import HX711
from w1thermsensor import W1ThermSensor


class BeerDispenser(object):
    def __init__(self):
        super(BeerDispenser, self).__init__()
        pg.init()
        self.screen = pg.display.set_mode((SWIDTH, SHEIGHT), pg.FULLSCREEN)
        pg.mouse.set_visible(True)  # change to False when using touch screen
        self.clock = pg.time.Clock()

        # Sets numeration of channels according to GPIO on Pi
        GPIO.setwarnings(False)
        GPIO.setmode(GPIO.BCM)

        # Set up GPIO pins
        GPIO.setup(21, GPIO.IN, pull_up_down=GPIO.PUD_UP)  # Button
        GPIO.setup(5, GPIO.OUT, initial=0)  # Magnetic valve, starts closed
        GPIO.setup(10, GPIO.IN)  # Temperature probe DS18S20
        GPIO.setup(2, GPIO.IN)  # Load sensor DT
        GPIO.setup(3, GPIO.OUT)  # Load sensor SCK

        GPIO.add_event_detect(21, GPIO.BOTH, callback=self.buttonSignal)

        # Load sensor
        hx = HX711(2, 3)
        hx.set_scale(92)  # Sets bit value for 1g
        hx.set_offset(0)  # This gets calibrated to zero the sensor

        # Parameters for dispenser
        self.running = True
        self.dispensing = False
        self.remainingVolume = self.kegVolume()
        self.buttonDown = False
        self.tempSensor = W1ThermSensor()
        self.temperature = self.tempSensor.get_temperature()

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

    def buttonOn(self):
        self.dispensing = True
        self.openValve()

    def buttonOff(self):
        self.shutValve()
        self.dispensing = False

    def kegVolume(self):
        dryKegVolume = 4000  # Dry weight of keg system
        wetKegVolume = int(hx.get_grams()) - dryKegVolume
        kegVolumeString = str(wetKegVolume)
        return kegVolumeString

    def drawToScreen(self, image, x, y):
        self.image = image
        image_rect = image.get_rect()
        image_rect.center = (x, y)
        self.screen.blit(image, image_rect)

    def kegVolumeDraw(self, size, x, y):
        if len(self.kegVolume()) == 1:
            self.drawToScreen(size[int(self.kegVolume())], x, y)
        if len(self.kegVolume()) == 2:
            self.drawToScreen(size[int(self.kegVolume()[0:1])], x-(13*RELX), y)
            self.drawToScreen(size[int(self.kegVolume()[1:2])], x+(13*RELX), y)
        if len(self.kegVolume()) == 3:
            self.drawToScreen(size[int(self.kegVolume()[0:1])], x-(25*RELX), y)
            self.drawToScreen(size[int(self.kegVolume()[1:2])], x, y)
            self.drawToScreen(size[int(self.kegVolume()[2:3])], x+(25*RELX), y)
        if len(self.kegVolume()) == 4:
            self.drawToScreen(size[int(self.kegVolume()[0:1])], x-(38*RELX), y)
            self.drawToScreen(size[int(self.kegVolume()[1:2])], x-(13*RELX), y)
            self.drawToScreen(size[int(self.kegVolume()[2:3])], x+(13*RELX), y)
            self.drawToScreen(size[int(self.kegVolume()[3:4])], x+(38*RELX), y)
        if len(self.kegVolume()) == 5:
            self.drawToScreen(size[int(self.kegVolume()[0:1])], x-(50*RELX), y)
            self.drawToScreen(size[int(self.kegVolume()[1:2])], x-(25*RELX), y)
            self.drawToScreen(size[int(self.kegVolume()[2:3])], x, y)
            self.drawToScreen(size[int(self.kegVolume()[3:4])], x+(25*RELX), y)
            self.drawToScreen(size[int(self.kegVolume()[4:5])], x+(50*RELX), y)

    def temperatureDraw(self):
        if 10 > self.temperature >= 0:
            self.drawToScreen(NEON_NUMBER_SCALED_MINI[self.temperature], (SWIDTH*0.55), (SHEIGHT*0.95))
        if self.temperature > 9:
            self.drawToScreen(NEON_NUMBER_SCALED_MINI[self.temperature[0:1]], (SWIDTH*0.55)-(13*RELX), (SHEIGHT*0.95))
            self.drawToScreen(NEON_NUMBER_SCALED_MINI[self.temperature[1:2]], (SWIDTH*0.55)+(13*RELX), (SHEIGHT*0.95))

    def dispensorEvents(self):
        if self.buttonDown:
            self.kegVolume = int(self.kegVolume)
            if self.kegVolume > 0:
                self.buttonOn()
            if self.kegVolume == 0:
                self.kegVolume = self.kegVolume()
        else:
            self.mouse = pg.mouse.get_pos()
            self.click = pg.mouse.get_pressed()
            self.keys = pg.key.get_pressed()
            if self.click[0] == 1:
                if self.mouse[0] > (SWIDTH-(200*RELX)) and self.mouse[1] > (SHEIGHT-(200*RELY)):
                    self.buttonOn()
                if self.mouse[0] < (50*RELX) and self.mouse[1] < (50*RELY):
                    self.running = False
            else:
                self.buttonOff()
                self.dispensing = False

            for event in pg.event.get():
                if event.type == pg.QUIT:
                    self.running = False
                if event.type == pg.KEYDOWN and event.key == pg.K_ESCAPE:
                    self.running = False

    def dispensorDraw(self):
        self.pintsLeft = int((int(self.kegVolume)+499)/500)
        self.drawToScreen(DISPENSOR_BACKGROUND, SWIDTH/2, SHEIGHT/2)
        if self.dispensing:
            self.drawToScreen(BUTTON_ON, SWIDTH-(100*RELX), SHEIGHT-(100*RELY))
        if not self.dispensing:
            self.drawToScreen(BUTTON, SWIDTH-(100*RELX), SHEIGHT-(100*RELY))
        if int(int(self.kegVolume())/500) <= 9:
            self.drawToScreen(NEON_NUMBER[int(str(self.pintsLeft))], (350*RELX), (475*RELY))
        if int(int(self.kegVolume())/500) > 9:
            self.drawToScreen(NEON_NUMBER[int(str(self.pintsLeft)[0:1])], (325*RELX), (475*RELY))
            self.drawToScreen(NEON_NUMBER[int(str(self.pintsLeft)[1:2])], (380*RELX), (475*RELY))
        self.kegVolumeDraw(NEON_NUMBER_SCALED_MINI, (SWIDTH*0.34), (SHEIGHT*0.95))
        self.temperatureDraw()
        self.drawToScreen(QUIT, (25*RELX), (25*RELY))
        pg.display.flip()

    def run(self):
        self.clock.tick(FPS)
        self.dispensorEvents()
        self.dispensorDraw()

if __name__ == '__main__':
    b = BeerDispenser()
    while b.running:
        try:
            b.run()
        except KeyboardInterrupt:
            b.running = False
    hx.reset()
    GPIO.cleanup()
    pg.quit()
