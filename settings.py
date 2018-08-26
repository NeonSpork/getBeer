"""Settings file for getBeerPG.
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

# Image files - run through scale transform (optimized for 1024x600)
dispensor_background = pg.image.load('img/background_screen_info.png')
DISPENSOR_BACKGROUND = pg.transform.scale(dispensor_background,
                                          (int(1024*RELX), int(600*RELY)))
intro_background = pg.image.load('img/splash_screen.png')
INTRO_BACKGROUND = pg.transform.scale(intro_background,
                                      (int(1024*RELX), int(600*RELY)))
button = pg.image.load('img/beer_button.png')
BUTTON = pg.transform.scale(button, (int(200*RELX), int(200*RELY)))
button_on = pg.image.load('img/beer_button1.png')
BUTTON_ON = pg.transform.scale(button_on, (int(200*RELX), int(200*RELY)))
quit = pg.image.load('img/exit.png')
QUIT = pg.transform.scale(quit, (int(50*RELX), int(50*RELY)))
delete = pg.image.load('img/delete.png')
DELETE = pg.transform.scale(delete, (int(100*RELX), int(100*RELY)))
done = pg.image.load('img/done.png')
DONE = pg.transform.scale(done, (int(100*RELX), int(100*RELY)))
NEON_NUMBER = []
enum = 0
for img in range(10):
    img = pg.image.load('img/num{}.png'.format(enum))
    imgscale = pg.transform.scale(img, (int(100*RELX), int(100*RELY)))
    NEON_NUMBER.append(imgscale)
    enum += 1
NEON_NUMBER_SCALED = []
enum_scaled = 0
for img in range(10):
    unscaled_img = pg.image.load('img/num{}.png'.format(enum_scaled))
    img = pg.transform.scale(unscaled_img, (int(50*RELX), int(50*RELY)))
    NEON_NUMBER_SCALED.append(img)
    enum_scaled += 1
NEON_NUMBER_SCALED_MINI = []
enum_scaled_mini = 0
for img in range(10):
    unscaled_img = pg.image.load('img/num{}.png'.format(enum_scaled_mini))
    img = pg.transform.scale(unscaled_img, (int(30*RELX), int(30*RELY)))
    NEON_NUMBER_SCALED_MINI.append(img)
    enum_scaled_mini += 1
