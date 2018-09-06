"""Settings file for getBeerPG.

TESTING
"""
import tkinter as tk
import pygame as pg


# Screen parameters
FPS = 60
# for testing:
# SWIDTH = 1024
# SHEIGHT = 600
root = tk.Tk()
SWIDTH = root.winfo_screenwidth()
SHEIGHT = root.winfo_screenheight()
RELX = SWIDTH/1024
RELY = SHEIGHT/600

# Colors
DARK_GREY = (25, 25, 25)
CYAN = (0, 255, 216)
MAGENTA = (233, 0, 255)
PURPLE = (179, 0, 255)

# Image files - run through scale transform to be compatible between various
# screen sizes (optimized for 1024x600)

# Background images
bricks = pg.image.load('img/bg/brick_wall.png')
BRICKS = pg.transform.scale(bricks, (int(1024*RELX), int(600*RELY)))
BACKGROUNDS = []
default_background = pg.image.load('img//bg/default_background.png')
DEFAULT_BACKGROUND = pg.transform.scale(default_background, (int(1024*RELX), int(600*RELY)))
BACKGROUNDS.append(DEFAULT_BACKGROUND)
tt_background = pg.image.load('img/bg/tropical_thunder_bg.png')
TT_BACKGROUND = pg.transform.scale(tt_background, (int(1024*RELX), int(600*RELY)))
BACKGROUNDS.append(TT_BACKGROUND)

# Beer thumbnails
THUMB = []
default_thumbnail = pg.image.load('img/icon/default_icon.png')
DEFAULT_THUMBNAIL = pg.transform.scale(default_thumbnail, (int(300*RELX), int(150*RELY)))
THUMB.append(DEFAULT_THUMBNAIL)
beer1 = pg.image.load('img/icon/tropical_thunder.png')
BEER1 = pg.transform.scale(beer1, (int(150*RELX), int(150*RELY)))
THUMB.append(BEER1)
coming_soon = pg.image.load('img/icon/coming_soon_thumb.png')
COMING_SOON = pg.transform.scale(coming_soon, (int(150*RELX), int(150*RELY)))


# Buttons & icons
button = pg.image.load('img/icon/beer_button.png')
BUTTON = pg.transform.scale(button, (int(200*RELX), int(200*RELY)))
button_on = pg.image.load('img/icon/beer_button1.png')
BUTTON_ON = pg.transform.scale(button_on, (int(200*RELX), int(200*RELY)))
quit = pg.image.load('img/icon/exit.png')
QUIT = pg.transform.scale(quit, (int(50*RELX), int(50*RELY)))
ml_icon = pg.image.load('img/icon/ml_icon.png')
ML_ICON = pg.transform.scale(ml_icon, (int(50*RELX), int(50*RELY)))
temp_icon = pg.image.load('img/icon/temp_icon.png')
TEMP_ICON = pg.transform.scale(temp_icon, (int(50*RELX), int(50*RELY)))
pints_icon = pg.image.load('img/icon/pints.png')
PINTS_ICON = pg.transform.scale(pints_icon, (int(200*RELX), int(100*RELY)))

# Image files for numbers
NEON_NUMBER = []
enum = 0
for img in range(10):
    img = pg.image.load('img/num/num{}.png'.format(enum))
    imgscale = pg.transform.scale(img, (int(100*RELX), int(100*RELY)))
    NEON_NUMBER.append(imgscale)
    enum += 1
NEON_NUMBER_SCALED = []
enum_scaled = 0
for img in range(10):
    unscaled_img = pg.image.load('img/num/num{}.png'.format(enum_scaled))
    img = pg.transform.scale(unscaled_img, (int(50*RELX), int(50*RELY)))
    NEON_NUMBER_SCALED.append(img)
    enum_scaled += 1
NEON_NUMBER_SCALED_MINI = []
enum_scaled_mini = 0
for img in range(10):
    unscaled_img = pg.image.load('img/num/num{}.png'.format(enum_scaled_mini))
    img = pg.transform.scale(unscaled_img, (int(25*RELX), int(25*RELY)))
    NEON_NUMBER_SCALED_MINI.append(img)
    enum_scaled_mini += 1
