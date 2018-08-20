"""getBeer.py _PyGame_version_

Using a button and flow meter getBeer dispenses beer at
the push of a button! Written and tested with PyGame 1.9.4.
PyGame was chosen partly due to familiarity with the API,
partly because it provides a very easy framework for a GUI
and it is MUCH more flexible than tkinter or ttk for making
stuff look cool.

Wiring the hardware:
Button          - GP21 (pin 40] & GND (pin 39)
Flow meter      - GP13 (pin 33) & GND (pin 34), and 3.3V pin for power
Magnetic valve  - GP5 (pin 29) & GND (pin 30)

See lcd.py for wiring the 16x2 LCD display.
"""

import sys
import pygame as pg
from settings import *
import RPi.GPIO as GPIO
import lcd


class BeerDispenser(object):
    def __init__(self):
        super(BeerDispenser, self).__init__()
        pg.init()
        pg.mouse.set_visible(True)
        self.screen = pg.display.set_mode((SWIDTH, SHEIGHT), pg.FULLSCREEN)
        self.clock = pg.time.Clock()
        
        # Sets numeration of channels according to pin numbers on Pi
        GPIO.setmode(GPIO.BOARD)
        GPIO.setwarnings(False)

        # Set up GPIO pins
        GPIO.setup(40, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)  # Button
        GPIO.setup(33, GPIO.IN)  # Flow meter
        GPIO.setup(29, GPIO.OUT, initial=0)  # Magnetic valve, starts closed

        # Initializing 16x2 lcd screen
        lcd.lcd_init()

        # Parameters for dispenser
        self.running = True
        self.dispensing = False
        self.kegVolume = ''
        self.dispensedBeer = 0

        self.intro = True
        self.dispensor = False

    def openValve(self):
        GPIO.output(29, True)

    def shutValve(self):
        GPIO.output(29, False)

    def countFlow(self):
        dispensedVolume = 0
        if GPIO.input(33):  # Pulse from flow meter
            dispensedVolume += 1  # Adjust this to whatever equates 1 ml
        return int(dispensedVolume)

    def buttonOn(self):
        self.dispensing = True
        self.openValve()
        self.kegVolume = int(self.kegVolume)
        if self.kegVolume > 0:
            self.buttonOn()
            self.dispensedBeer += 1  # self.countFlow()
            self.kegVolume -= int(self.dispensedBeer)
            self.dispensing = True
        if self.kegVolume == 0:
                self.kegVolume = str(self.kegVolume)

    def buttonOff(self):
        self.shutValve()
        self.dispensing = False

    def drawToLittleScreen(self, message, line):
        lcd.lcd_clear()
        if line == 1:
            lcd.lcd_string(message, LCD_LINE_1)
        if line == 2:
            lcd.lcd_string(message, LCD_LINE_2)

    def drawImageToBigScreen(self, image, x, y):
        self.image = image
        image_rect = image.get_rect()
        image_rect.center = (x, y)
        self.screen.blit(image, image_rect)

    def kegVolumeDraw(self, size, x, y):
        if len(str(self.kegVolume)) == 1:
            self.drawImageToBigScreen(size[int(str(self.kegVolume))], x, y)
        if len(str(self.kegVolume)) == 2:
            self.drawImageToBigScreen(size[int(str(self.kegVolume)[0:1])], x-(13*RELX), y)
            self.drawImageToBigScreen(size[int(str(self.kegVolume)[1:2])], x+(13*RELX), y)
        if len(str(self.kegVolume)) == 3:
            self.drawImageToBigScreen(size[int(str(self.kegVolume)[0:1])], x-(25*RELX), y)
            self.drawImageToBigScreen(size[int(str(self.kegVolume)[1:2])], x, y)
            self.drawImageToBigScreen(size[int(str(self.kegVolume)[2:3])], x+(25*RELX), y)
        if len(str(self.kegVolume)) == 4:
            self.drawImageToBigScreen(size[int(str(self.kegVolume)[0:1])], x-(38*RELX), y)
            self.drawImageToBigScreen(size[int(str(self.kegVolume)[1:2])], x-(13*RELX), y)
            self.drawImageToBigScreen(size[int(str(self.kegVolume)[2:3])], x+(13*RELX), y)
            self.drawImageToBigScreen(size[int(str(self.kegVolume)[3:4])], x+(38*RELX), y)
        if len(str(self.kegVolume)) == 5:
            self.drawImageToBigScreen(size[int(str(self.kegVolume)[0:1])], x-(50*RELX), y)
            self.drawImageToBigScreen(size[int(str(self.kegVolume)[1:2])], x-(25*RELX), y)
            self.drawImageToBigScreen(size[int(str(self.kegVolume)[2:3])], x, y)
            self.drawImageToBigScreen(size[int(str(self.kegVolume)[3:4])], x+(25*RELX), y)
            self.drawImageToBigScreen(size[int(str(self.kegVolume)[4:5])], x+(50*RELX), y)
        self.drawImageToBigScreen(QUIT, (25*RELX), (25*RELY))

    def introDraw(self):
        self.screen.fill(DARK_GREY)
        self.drawImageToBigScreen(INTRO_BACKGROUND, SWIDTH/2, SHEIGHT/2)
        self.drawImageToBigScreen(NEON_NUMBER[7], ((SWIDTH/2)-(100*RELX)), ((SHEIGHT/2)-(100*RELY)))
        self.drawImageToBigScreen(NEON_NUMBER[8], (SWIDTH/2), ((SHEIGHT/2)-(100*RELY)))
        self.drawImageToBigScreen(NEON_NUMBER[9], ((SWIDTH/2)+(100*RELX)), ((SHEIGHT/2)-(100*RELY)))
        self.drawImageToBigScreen(NEON_NUMBER[4], ((SWIDTH/2)-(100*RELX)), (SHEIGHT/2))
        self.drawImageToBigScreen(NEON_NUMBER[5], (SWIDTH/2), (SHEIGHT/2))
        self.drawImageToBigScreen(NEON_NUMBER[6], ((SWIDTH/2)+(100*RELX)), (SHEIGHT/2))
        self.drawImageToBigScreen(NEON_NUMBER[1], ((SWIDTH/2)-(100*RELX)), ((SHEIGHT/2)+(100*RELY)))
        self.drawImageToBigScreen(NEON_NUMBER[2], (SWIDTH/2), ((SHEIGHT/2)+(100*RELY)))
        self.drawImageToBigScreen(NEON_NUMBER[3], ((SWIDTH/2)+(100*RELX)), ((SHEIGHT/2)+(100*RELY)))
        self.drawImageToBigScreen(DELETE, ((SWIDTH/2)-(100*RELX)), ((SHEIGHT/2)+(200*RELY)))
        self.drawImageToBigScreen(NEON_NUMBER[0], (SWIDTH/2), ((SHEIGHT/2)+(200*RELY)))
        self.drawImageToBigScreen(DONE, ((SWIDTH/2)+(100*RELX)), ((SHEIGHT/2)+(200*RELY)))
        self.kegVolumeDraw(NEON_NUMBER_SCALED, (SWIDTH/2), (SHEIGHT/2)-(175*RELY))
        self.drawImageToBigScreen(QUIT, (25*RELX), (25*RELY))
        pg.display.flip()

    def dispensorDraw(self):
        self.pintsLeft = int((int(self.kegVolume)+499)/500)
        self.drawImageToBigScreen(DISPENSOR_BACKGROUND, SWIDTH/2, SHEIGHT/2)
        if self.dispensing:
            self.drawImageToBigScreen(BUTTON_ON, SWIDTH-(100*RELX), SHEIGHT-(100*RELY))
            self.drawToLittleScreen('{} ml tapped,'.format(self.dispensedBeer), 1)
            self.drawToLittleScreen('{} pints left.'.format(self.pintsLeft), 2)
        if not self.dispensing:
            self.drawImageToBigScreen(BUTTON, SWIDTH-(100*RELX), SHEIGHT-(100*RELY))
            self.drawToLittleScreen('Volume remaining', 1)
            self.drawToLittleScreen('{} ml'.format(self.kegVolume), 2)
        if int(int(self.kegVolume)/500) <= 9:
            self.drawImageToBigScreen(NEON_NUMBER[int(str(self.pintsLeft))], (350*RELX), (475*RELY))
        if int(int(self.kegVolume)/500) > 9:
            self.drawImageToBigScreen(NEON_NUMBER[int(str(self.pintsLeft)[0:1])], (325*RELX), (475*RELY))
            self.drawImageToBigScreen(NEON_NUMBER[int(str(self.pintsLeft)[1:2])], (380*RELX), (475*RELY))
        self.kegVolumeDraw(NEON_NUMBER_SCALED_MINI, ((SWIDTH*0.34)), (SHEIGHT*0.95))
        self.drawImageToBigScreen(QUIT, (25*RELX), (25*RELY))
        pg.display.flip()

    def introEvents(self):
        self.mouse = pg.mouse.get_pos()
        self.click = pg.mouse.get_pressed()
        self.keys = pg.key.get_pressed()
        if self.keys[pg.K_ESCAPE]:
            self.running = False

        for event in pg.event.get():
            if event.type == pg.QUIT:
                pg.quit()
                self.running = False
            if event.type == pg.KEYDOWN and event.key == pg.K_ESCAPE:
                self.running = False
            if event.type == pg.MOUSEBUTTONDOWN and event.button == 1:
                x, y = SWIDTH/2, SHEIGHT/2
                if self.mouse[0] < (50*RELX) and self.mouse[1] < (50*RELY):
                    self.running = False
                if (x-(50*RELX)) > self.mouse[0] > (x-(150*RELX)) and (y-(50*RELY)) > self.mouse[1] > (y-(150*RELY)):
                    if len(str(self.kegVolume)) == 1 and str(self.kegVolume)[0:1] == '0':
                        self.kegVolume = '7'
                    elif len(str(self.kegVolume)) < 5:
                        self.kegVolume += '7'
                if (x+(50*RELX)) > self.mouse[0] > (x-(50*RELX)) and (y-(50*RELY)) > self.mouse[1] > (y-(150*RELY)):
                    if len(str(self.kegVolume)) == 1 and str(self.kegVolume)[0:1] == '0':
                        self.kegVolume = '8'
                    elif len(str(self.kegVolume)) < 5:
                        self.kegVolume += '8'
                if (x+(150*RELX)) > self.mouse[0] > (x+(50*RELX)) and (y-(50*RELY)) > self.mouse[1] > (y-(150*RELY)):
                    if len(str(self.kegVolume)) == 1 and str(self.kegVolume)[0:1] == '0':
                        self.kegVolume = '9'
                    elif len(str(self.kegVolume)) < 5:
                        self.kegVolume += '9'
                if (x-(50*RELX)) > self.mouse[0] > (x-(150*RELX)) and (y+(50*RELY)) > self.mouse[1] > (y-(50*RELY)):
                    if len(str(self.kegVolume)) == 1 and str(self.kegVolume)[0:1] == '0':
                        self.kegVolume = '4'
                    elif len(str(self.kegVolume)) < 5:
                        self.kegVolume += '4'
                if (x+(50*RELX)) > self.mouse[0] > (x-(50*RELX)) and (y+(50*RELY)) > self.mouse[1] > (y-(50*RELY)):
                    if len(str(self.kegVolume)) == 1 and str(self.kegVolume)[0:1] == '0':
                        self.kegVolume = '5'
                    elif len(str(self.kegVolume)) < 5:
                        self.kegVolume += '5'
                if (x+(150*RELX)) > self.mouse[0] > (x+(50*RELX)) and (y+(50*RELY)) > self.mouse[1] > (y-(50*RELY)):
                    if len(str(self.kegVolume)) == 1 and str(self.kegVolume)[0:1] == '0':
                        self.kegVolume = '6'
                    elif len(str(self.kegVolume)) < 5:
                        self.kegVolume += '6'
                if (x-(50*RELX)) > self.mouse[0] > (x-(150*RELX)) and (y+(150*RELY)) > self.mouse[1] > (y+(50*RELY)):
                    if len(str(self.kegVolume)) == 1 and str(self.kegVolume)[0:1] == '0':
                        self.kegVolume = '1'
                    elif len(str(self.kegVolume)) < 5:
                        self.kegVolume += '1'
                if (x+(50*RELX)) > self.mouse[0] > (x-(50*RELX)) and (y+(150*RELY)) > self.mouse[1] > (y+(50*RELY)):
                    if len(str(self.kegVolume)) == 1 and str(self.kegVolume)[0:1] == '0':
                        self.kegVolume = '2'
                    elif len(str(self.kegVolume)) < 5:
                        self.kegVolume += '2'
                if (x+(150*RELX)) > self.mouse[0] > (x+(50*RELX)) and (y+(150*RELY)) > self.mouse[1] > (y+(50*RELY)):
                    if len(str(self.kegVolume)) == 1 and str(self.kegVolume)[0:1] == '0':
                        self.kegVolume = '3'
                    elif len(str(self.kegVolume)) < 5:
                        self.kegVolume += '3'
                if (x-(50*RELX)) > self.mouse[0] > (x-(150*RELX)) and (y+(250*RELY)) > self.mouse[1] > (y+(150*RELY)):
                    # Deletes last character of self.kegVolume
                    deleteLastChar = str(self.kegVolume)[:-1]
                    self.kegVolume = deleteLastChar
                if (x+(50*RELX)) > self.mouse[0] > (x-(50*RELX)) and (y+(250*RELY)) > self.mouse[1] > (y+(150*RELY)):
                    if 0 < len(str(self.kegVolume)) <= 4:
                        self.kegVolume += '0'
                if (x+(150*RELX)) > self.mouse[0] > (x+(50*RELX)) and (y+(250*RELY)) > self.mouse[1] > (y+(150*RELY)):
                    # Ends volume input and moves to next screen
                    self.intro = False
                    self.dispensor = True

    def dispensorEvents(self):
        self.mouse = pg.mouse.get_pos()
        self.click = pg.mouse.get_pressed()
        self.keys = pg.key.get_pressed()
        if self.keys[pg.K_ESCAPE]:
            self.running = False

        # if self.buttonDown:
        #     self.kegVolume = int(self.kegVolume)
        #     if self.kegVolume > 0:
        #         self.buttonOn()
        #         self.dispensedBeer += self.countFlow()
        #         self.kegVolume -= int(self.dispensedBeer)
        #         self.dispensing = True
        #     if self.kegVolume == 0:
        #             self.kegVolume = str(self.kegVolume)

        if self.click[0] == 1:
            if self.mouse[0] > (SWIDTH-(200*RELX)) and self.mouse[1] > (SHEIGHT-(200*RELY)):
                self.kegVolume = int(self.kegVolume)
                if self.kegVolume > 0:
                    print(self.kegVolume)
                    self.buttonOn()
                    self.dispensedBeer += self.countFlow()
                    self.kegVolume -= int(self.dispensedBeer)
                    self.dispensing = True
                if self.kegVolume == 0:
                    self.kegVolume = str(self.kegVolume)
            if self.mouse[0] < (50*RELX) and self.mouse[1] < (50*RELY):
                self.dispensor = False
                self.intro = True
        if not self.click[0]:
            self.dispensedBeer = 0
            self.dispensing = False
        else:
            self.buttonOff()
            self.dispensedBeer = 0
            self.dispensing = False

        for event in pg.event.get():
            if event.type == pg.QUIT:
                pg.quit()
                self.running = False
            if event.type == pg.KEYDOWN and event.key == pg.K_ESCAPE:
                self.intro = True
                self.dispensor = False

    def run(self):
        self.clock.tick(FPS)
        if self.intro is True and self.dispensor is False:
            self.introDraw()
            self.introEvents()
        if self.intro is False and self.dispensor is True:
            self.dispensorDraw()
            self.dispensorEvents()

if __name__ == '__main__':
    b = BeerDispenser()
    GPIO.add_event_detect(40, GPIO.RISING, callback=b.buttonOn())
    while b.running:
        try:
            b.run()
        except KeyboardInterrupt:
            b.running = False
    GPIO.cleanup()
    pg.quit()
    sys.exit()
