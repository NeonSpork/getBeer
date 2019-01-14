#!/bin/sh

cd -/getBeer
/usr/bin/git checkout master
/usr/bin/git pull

cd ~/getBeer/getBeer_python
/usr/bin/python3 getBeer.py

exit 0