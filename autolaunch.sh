#!/bin/sh
# Add crontab entry to automagically run
# getBeer autostart shell at reboot:
# $ sudo nano /home/pi/.config/lxsession/LXDE-pi/autostart
# add the following line at the bottom:
# @sh /home/pi/getBeer/autolaunch.sh

cd /home/pi/getBeer
/usr/bin/python3 getBeer.py

exit 0
