#ifndef HX711_H
#define HX711_H

#include <stdint.h>
#include <wiringPi.h>

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

typedef uint8_t byte;

class HX711
{
public:
  HX711(uint8_t pin_dout, uint8_t pin_slk);
  virtual ~HX711();
  long getValue();
  long averageValue(byte times = 32);
  void setOffset(long offset);
  void setScale(float scale);
  float getGrams(byte times = 32);
private:
  const uint8_t _pin_dout;
  const uint8_t _pin_slk;
  long _offset;
  float _scale;
};

#endif