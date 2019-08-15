"""getBeer TOP SECRET SIMPLE

TESTER FOR MAKING SURE EVERYTHING IS DISPLAYING CORRECTLY

Control unit for beer dispenser built into kegerator.

Wiring the hardware:
Magnetic valve  - GP5 (pin 29) & GND (pin 30)
Temperature - GP4 (pin 7), GND (pin 20) & 3v3 (pin 1)
Load sensor - VCC=3v3 (pin 17), GND (pin 9), DT=GP2 (pin 3), SCK=GP3 (pin 5)
See LCD for wiring 16x2 display
"""

import sys
import pygame as pg
from settings import *


def kegVolume():
    dryKegWeight = 4025
    wetKegVolume = 28700 - dryKegWeight
    if wetKegVolume < 0:
        wetKegVolume = 0
    return wetKegVolume


def kegTemp():
    kegTemperature = 7
    return kegTemperature


class BeerDispenser(object):
    def __init__(self):
        super(BeerDispenser, self).__init__()
        pg.init()
        self.screen = pg.display.set_mode((SWIDTH, SHEIGHT))
        self.clock = pg.time.Clock()

        # Parameters for dispenser
        self.running = True
        self.dispensing = False
        self.dispensingSecret = False
        self.bg_image = 0
        self.dispenserDisplay = True
        self.beerChooser = False
        self.secretActive = False
        self.secretTimer = 0
        self.secretTimeIdle = 0
        self.pintsLeft = 0
        self.counter = 0

    def openValve(self):
        print("Valve opened.")
        self.dispensing = True

    def shutValve(self):
        self.dispensing = False

    def openSecretValve(self):
        print("Secret valve opened.")
        self.dispensingSecret = True

    def shutSecretValve(self):
        self.dispensingSecret = False

    def dispenserEvents(self):
        self.mouse = pg.mouse.get_pos()
        self.click = pg.mouse.get_pressed()
        self.keys = pg.key.get_pressed()
        if self.click[0] == 1:
            if self.mouse[0] > (SWIDTH-(200*RELX)) and self.mouse[1] > (SHEIGHT-(200*RELY)):
                self.openValve()
            if self.mouse[0] < (100*RELX) and self.mouse[1] < (100*RELY):
                self.dispenserDisplay = False
                self.secretActive = False
                self.beerChooser = True
                print("Switched to beerChooser")
                pg.time.delay(100)
            if self.mouse[0] > (SWIDTH-(50*RELX)) and self.mouse[1] < (50*RELY):
                self.running = False
            if self.bg_image == 0:
                if (575*RELX) < self.mouse[0] < (825*RELX) and (25*RELY) < self.mouse[1] < (125*RELY):
                    if self.secretTimer <= (FPS*3):
                        self.secretTimer += 1
                        print(self.secretTimer)
                    if self.secretTimer > (FPS*3):
                        self.secretActive = True
                        self.secretTimeIdle = 0
                        self.openSecretValve()
        else:
            self.shutValve()
            self.shutSecretValve()
            if self.secretTimeIdle <= (FPS*3):
                self.secretTimeIdle += 1
            if self.secretTimeIdle > (FPS*3):
                self.secretActive = False
                self.secretTimer = 0
        for event in pg.event.get():
            if event.type == pg.QUIT:
                self.running = False
            if event.type == pg.KEYDOWN and event.key == pg.K_ESCAPE:
                self.running = False

    def dispenserDraw(self):
        try:
            self.drawToScreen(BACKGROUNDS[self.bg_image], SWIDTH/2, SHEIGHT/2)
        except IndexError:
            self.drawToScreen(DEFAULT_BACKGROUND, SWIDTH/2, SHEIGHT/2)
        if self.dispensing:
            if self.bg_image == 2:
                self.drawToScreen(RED_BUTTON_ON, SWIDTH-(100*RELX), SHEIGHT-(100*RELY))
            else:
                self.drawToScreen(BUTTON_ON, SWIDTH-(100*RELX), SHEIGHT-(100*RELY))
        if not self.dispensing:
            if self.bg_image == 2:
                self.drawToScreen(RED_BUTTON, SWIDTH-(100*RELX), SHEIGHT-(100*RELY))
            else:
                self.drawToScreen(BUTTON, SWIDTH-(100*RELX), SHEIGHT-(100*RELY))
        if self.bg_image == 0:
            if self.secretActive:
                if self.dispensingSecret:
                    self.drawToScreen(SECRET_ICON_ON, (525*RELX), (75*RELY))
                else:
                    self.drawToScreen(SECRET_ICON_OFF, (525*RELX), (75*RELY))
        self.drawToScreen(PINTS_ICON, (SWIDTH*0.1), (SHEIGHT*0.9))
        if int(self.pintsLeft) < 10:
            self.drawToScreen(NEON_NUMBER[int(str(self.pintsLeft))], (SWIDTH*0.28), (SHEIGHT*0.9))
        if int(self.pintsLeft) >= 10:
            self.drawToScreen(NEON_NUMBER[int(str(self.pintsLeft)[0:1])], ((SWIDTH*0.28)-(30*RELX)), (SHEIGHT*0.9))
            self.drawToScreen(NEON_NUMBER[int(str(self.pintsLeft)[1:2])], ((SWIDTH*0.28)+(30*RELX)), (SHEIGHT*0.9))
        if int(self.currentTemp) < 10:
            self.drawToScreen(NEON_NUMBER_SCALED_MINI[int(str(self.currentTemp)[0:1])], (SWIDTH*0.1), (SHEIGHT*0.96))
            self.drawToScreen(TEMP_ICON, ((SWIDTH*0.1)+(20*RELX)), (SHEIGHT*0.96))
        if int(self.currentTemp) >= 10:
            self.drawToScreen(NEON_NUMBER_SCALED_MINI[int(str(self.currentTemp)[0:1])], ((SWIDTH*0.1)-(5*RELX)), (SHEIGHT*0.96))
            self.drawToScreen(NEON_NUMBER_SCALED_MINI[int(str(self.currentTemp)[1:2])], ((SWIDTH*0.1)+(5*RELX)), (SHEIGHT*0.96))
        self.drawToScreen(TEMP_ICON, ((SWIDTH*0.1)+(30*RELX)), (SHEIGHT*0.96))
        self.drawToScreen(QUIT, (25*RELX), (25*RELY))
        pg.display.flip()

    def drawToScreen(self, image, x, y):
        self.image = image
        image_rect = image.get_rect()
        image_rect.center = (x, y)
        self.screen.blit(image, image_rect)

    def beerChooserEvents(self):
        self.mouse = pg.mouse.get_pos()
        self.click = pg.mouse.get_pressed()
        self.keys = pg.key.get_pressed()
        x, y = SWIDTH/2, SHEIGHT/2
        if self.click[0] == 1:
            if self.mouse[0] < (100*RELX) and self.mouse[1] < (100*RELY):
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

    def updateWeightTemp(self):
        self.pintsLeft = int(kegVolume()/500)
        self.currentTemp = int(kegTemp())

    def eventUpdate(self):
        if self.dispenserDisplay:
            self.dispenserEvents()
        if self.beerChooser:
            self.beerChooserEvents()

    def eventDraw(self):
        if self.dispenserDisplay:
            self.dispenserDraw()
        if self.beerChooser:
            self.beerChooserDraw()

    def run(self):
        self.clock.tick(FPS)
        print(self.clock.get_fps())
        self.eventUpdate()
        self.eventDraw()
        self.counter += 1
        if self.counter > FPS:
            self.updateWeightTemp()
            self.counter = 0

    def mainLoop(self):
        while self.running:
            try:
                self.run()
            except KeyboardInterrupt:
                self.running = False


if __name__ == '__main__':
    b = BeerDispenser()
    b.updateWeightTemp()
    while b.running:
        b.mainLoop()
    pg.quit()
    sys.exit()
