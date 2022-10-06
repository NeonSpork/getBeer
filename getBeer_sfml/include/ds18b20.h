#ifndef DS18B20_H_
#define DS18B20_H_

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

class Ds18b20
{
public:
  Ds18b20();
  virtual ~Ds18b20();
  void init();
  float getTemp();
  class NoDir{};
  class NoInit{};
  class NoRead{};
private:
  DIR *dir;
  struct dirent *dirent;
  char dev[16];      // Dev ID
  char devPath[128]; // Path to device
  char buf[256];     // Data from device
  char tmpData[6];   // Temp C * 1000 reported by device 
  ssize_t numRead;
};

#endif /* DS18B20_H_ */