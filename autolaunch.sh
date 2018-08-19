#!/bin/sh
# Add crontab entry to automagically run
# getBeer autostart shell at reboot:
# $ crontab -e
# @reboot /home/pi/getBeer/autolaunch.sh

cd /home/pi/getBeer

tmux new -s beer
tmux send-keys -t beer 'python3 getBeer.py' C-m
