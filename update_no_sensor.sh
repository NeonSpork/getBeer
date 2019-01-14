#!/bin/sh

cd ~/getBeer/
/usr/bin/git pull
/usr/bin/git checkout nosensor
/usr/bin/git pull

cd ~/getBeer/getBeer_sfml/build
/usr/bin/cmake .. -DRASPBERRY=TRUE -DCMAKE_BUILD_TYPE=Release -L
/usr/bin/make

cd ~/getBeer/getBeer_sfml/
./getBeerX

exit 0