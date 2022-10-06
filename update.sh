#!/bin/sh
# Asus Tinker Board:
# sudo nano /etc/xdg/lxsession/LXDE/autostart
# @sh ~/getBeer/update.sh
# However, it is SUPER hard to get this working properly apparently
# Recommend copying this shell script to desktop and double clicking it
# to start getBeer...

cd ~/getBeer/getBeer_sfml
/usr/bin/git pull
/usr/bin/git checkout master
/usr/bin/git pull

/usr/bin/scons

./getBeerX

exit 0