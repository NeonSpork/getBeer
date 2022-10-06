"""Settings file for getBeerPG.

TESTING
"""
import tkinter as tk
import pygame as pg


# Screen parameters
FPS = 12
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
babushka_background = pg.image.load('img/bg/angry_babushka_bg.png')
BABUSHKA_BACKGROUND = pg.transform.scale(babushka_background, (int(1024*RELX), int(600*RELY)))
BACKGROUNDS.append(BABUSHKA_BACKGROUND)

# Beer thumbnails
THUMB = []
default_thumbnail = pg.image.load('img/icon/default_icon.png')
DEFAULT_THUMBNAIL = pg.transform.scale(default_thumbnail, (int(300*RELX), int(150*RELY)))
THUMB.append(DEFAULT_THUMBNAIL)
beer1 = pg.image.load('img/icon/tropical_thunder_icon.png')
BEER1 = pg.transform.scale(beer1, (int(150*RELX), int(150*RELY)))
THUMB.append(BEER1)
beer2 = pg.image.load('img/icon/angry_babushka_icon.png')
BEER2 = pg.transform.scale(beer2, (int(150*RELX), int(150*RELY)))
THUMB.append(BEER2)
coming_soon = pg.image.load('img/icon/coming_soon_thumb.png')
COMING_SOON = pg.transform.scale(coming_soon, (int(150*RELX), int(150*RELY)))


# Buttons & icons
CURSOR = pg.image.load('img/icon/cursor.png')
button = pg.image.load('img/icon/beer_button_off.png')
BUTTON = pg.transform.scale(button, (int(200*RELX), int(200*RELY)))
button_on = pg.image.load('img/icon/beer_button_on.png')
BUTTON_ON = pg.transform.scale(button_on, (int(200*RELX), int(200*RELY)))
red_button = pg.image.load('img/icon/beer_button_red_off.png')
RED_BUTTON = pg.transform.scale(red_button, (int(200*RELX), int(200*RELY)))
red_button_on = pg.image.load('img/icon/beer_button_red_on.png')
RED_BUTTON_ON = pg.transform.scale(red_button_on, (int(200*RELX), int(200*RELY)))
quit = pg.image.load('img/icon/exit.png')
QUIT = pg.transform.scale(quit, (int(50*RELX), int(50*RELY)))
ml_icon = pg.image.load('img/icon/ml_icon.png')
ML_ICON = pg.transform.scale(ml_icon, (int(50*RELX), int(50*RELY)))
temp_icon = pg.image.load('img/icon/temp_icon.png')
TEMP_ICON = pg.transform.scale(temp_icon, (int(30*RELX), int(30*RELY)))  # Was 50x50 before
pints_icon = pg.image.load('img/icon/pints.png')
PINTS_ICON = pg.transform.scale(pints_icon, (int(200*RELX), int(100*RELY)))
secret_icon_on = pg.image.load('img/icon/secret_on.png')
SECRET_ICON_ON = pg.transform.scale(secret_icon_on, (int(50*RELX), int(50*RELY)))
secret_icon_off = pg.image.load('img/icon/secret_off.png')
SECRET_ICON_OFF = pg.transform.scale(secret_icon_off, (int(50*RELX), int(50*RELY)))

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


"""
This script includes a function that can compile cursor data from an image.
There are both advantages and disadvantages to using a real cursor over an
image that follows the mouse. See the documentation at the top of the example
script for more details.
-Sean McKiernan
"""


def cursor_from_image(image, size, hotspot, location=(0, 0), flip=False):
    """
    This function's return value is of the form accepted by
    pg.mouse.set_cursor() (passed using the *args syntax). The argument image
    is an already loaded image surface containing your desired cursor; size is
    a single integer corresponding to the width of the cursor (must be a
    multiple of 8); hotspot is a 2-tuple representing the exact point in your
    cursor that will represent the mouse position; location is a 2-tuple for
    where your cursor is located on the passed in image. Setting flip to True
    will create the cursor with colors opposite to the source image.
    Color in image to color in cursor defaults:
        Black (  0,   0,   0) ---> Black
        White (255, 255, 255) ---> White
        Cyan  (  0, 255, 255) ---> Xor (only available on certain systems)
        Any Other Color ---------> Transparent
    """
    if size % 8:
        raise ValueError("Size must be a multiple of 8.")
    compile_args = (".", "X", "o") if flip else ("X", ".", "o")
    colors = {(0, 0, 0, 255): ".",
              (255, 255, 255, 255): "X",
              (0, 255, 255, 255): "o"}
    cursor_string = []
    for j in range(size):
        this_row = []
        for i in range(size):
            where = (i+location[0], j+location[1])
            pixel = tuple(image.get_at(where))
            this_row.append(colors.get(pixel, " "))
        cursor_string.append("".join(this_row))
    xors, ands = pg.cursors.compile(cursor_string, *compile_args)
    size = size, size
    return size, hotspot, xors, ands
