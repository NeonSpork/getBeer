#ifndef HX711_H
#define HX711_H

#include <stdint.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <wiringPi.h>

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

typedef uint8_t byte;

class HX711
{
public:
  HX711(unsigned int pin_dout, unsigned int pin_slk);
  virtual ~HX711();
  long getValue();
  long averageValue(byte times = 32);
  void setOffset(long offset);
  long getOffset();
  void setScale(float scale);
  float getScale();
  float getGramsAverage(byte times = 32);
  float getGrams();
private:
  const unsigned int _pin_dout;
  const unsigned int _pin_slk;
  long _offset;
  float _scale;
};

#endif