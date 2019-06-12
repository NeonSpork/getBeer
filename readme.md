readme.md

# Custom beer dispenser for a kegerator

WORK IN PROGRESS

## Equipment
* Raspberry Pi 3
* HX711 weight sensor (to calculate volume)
* DS18B20 temperature sensor
* 1024*600 7" touch screen (HDMI)
* 16*2 LCD mini display (optional - we opted out)
* Some wire
* Beer
* Daydreams about beer dispensors

## Pictures

WORK IN PROGRESS

## Code
Should be able to clone directly into raspberry pi
### Dependencies - Python
* PyGame 1.9.4 
* W1ThermSensor
### Dependencies - CPP
* SFML 2.5.1
  * Be aware the apt-get version for Pi is outdated and this needs to be compiled from source including dependencies for SFML
* wiringPi
  * http://wiringpi.com/
### Building and compiling
#### CMAKE commands
* mkdir build
* cd build
* cmake .. -L
  * Remember to install the dependencies for SFML, a complete list can be found here: https://www.sfml-dev.org/tutorials/2.5/compile-with-cmake.php
* make
#### SCons commands
* scons
  * Builds the program as an executable
  * Remember to install the dependencies for SFML, a complete list can be found here: https://www.sfml-dev.org/tutorials/2.5/compile-with-cmake.php
