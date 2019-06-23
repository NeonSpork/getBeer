# Custom beer dispenser for a kegerator

WORK IN PROGRESS

## Equipment
* Raspberry Pi 3
  * Currently working on implementing C++ code on an Asus Tinker Board, in the hopes that it will run more smoothly. The graphics combined with the sensors push the RPi3 to the limits and then some.
  * Recommend using the program from the `nosensor` branch if you're using a Raspberry Pi 3 for a much more responsive performance.
* HX711 weight sensor (to calculate volume)
* DS18B20 temperature sensor
* 1024*600 7" touch screen (HDMI)
* 16*2 LCD mini display (optional - we opted out)
* Some wire
* Beer
* Daydreams about beer dispensors

## Pictures
Main screen, push button for beer!
![Imgur](https://i.imgur.com/2BQso9Q.jpg)

Installed in the final product.
![Imgur](https://i.imgur.com/OJeiuH8.jpg)

Alternate backgrounds, the button updates too! (More to come in the future)
![Imgur](https://i.imgur.com/vd8A6uum.png)
![Imgur](https://i.imgur.com/EzW6KZr.png)


## Code
Should be able to clone directly into raspberry pi
### Dependencies - Python
* PyGame 1.9.4 
* W1ThermSensor
### Dependencies - CPP *(see below for an easy way to install dependencies)*
* SFML 2.5.1
  * Be aware the apt-get version for Pi is outdated and this needs to be compiled from source including dependencies for SFML
* wiringPi
  * http://wiringpi.com/
### Building and compiling
#### CMAKE commands
* `mkdir build`
* `cd build`
* `cmake .. -L`
  * Remember to install the dependencies for SFML, a complete list can be found here: https://www.sfml-dev.org/tutorials/2.5/compile-with-cmake.php
* `make install`
#### SCons commands
* `scons`
  * Builds the program as an executable
  * Remember to install the dependencies for SFML, a complete list can be found here: https://www.sfml-dev.org/tutorials/2.5/compile-with-cmake.php
  * See below for the *lazy, easy peasy* way to install all the dependencies!
* Command flags for scons (LINUX ONLY)
  * `sudo scons install_SFML=1`
    * Clones into SFML git, compiles SFML
    * Installs SFML plus all the dependencies necessary on linux
    * Removes SFML directory when complete
  * `sudo scons install_wiringPi=1`
    * Clones into wiringPi library and installs it
    * Removes directory when complete
  * Flags can be combined!
    * `sudo scons install_SFML=1 install_wiringPi=1`