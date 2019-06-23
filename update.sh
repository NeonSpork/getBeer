#!/bin/sh

cd ~/getBeer/getBeer_sfml
/usr/bin/git pull
/usr/bin/git checkout master
/usr/bin/git pull

/usr/bin/scons

./getBeerX

exit 0