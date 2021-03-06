#!/bin/sh
# To automagically run getBeer autostart shell at reboot:
### GUI / desktop version
# $ sudo nano /home/pi/.config/lxsession/LXDE-pi/autostart
# add the following line at the bottom:
# @sh /home/pi/getBeer/getBeer_python/autolaunch.sh
### CLI version
# $ crontab -e
# add the following line at the bottom:
# @reboot /home/pi/getBeer/getBeer_python/autolaunch.sh > /home/pi/getBeer/getBeer_python/beer.log 2>&1

cd /home/pi/getBeer/getBeer_python
/usr/bin/python3 getBeer.py
# change the file name to whatever is appropriate
# for example getBeer_touch.py or getBeer_headless.py

exit 0
