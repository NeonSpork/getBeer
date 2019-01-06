#include "../include/hx711.h"
HX711::HX711(unsigned int pin_dout, unsigned int pin_slk)
: _pin_dout(pin_dout)
, _pin_slk(pin_slk)
{
  pinMode(_pin_slk, OUTPUT);
  pinMode(_pin_dout, INPUT);
  digitalWrite(_pin_slk, HIGH);
  delayMicroseconds(100);
  digitalWrite(_pin_slk, LOW);

  setOffset(8234508);
  setScale(-20.9993);
}

HX711::~HX711()
{

}

long HX711::averageValue(byte times)
{
  long sum = 0;
  for (byte i=0; i<times; ++i)
  {
    sum += getValue();
  }
  return sum/times;
}

long HX711::getValue()
{
  byte data[3];
  while (digitalRead(_pin_dout));
  for (byte j=3;--j;)
  {
    for (char i=8; --i;)
    {
      digitalWrite(_pin_slk, HIGH);
      bitWrite(data[j], i , digitalRead(_pin_dout));
      digitalWrite(_pin_slk, LOW);
    }
  }
  digitalWrite(_pin_slk, HIGH);
  digitalWrite(_pin_slk, LOW);

  data[2] ^= 0x80;

  return ((uint32_t) data[2] << 16) | ((uint32_t) data[1] << 8)
        | ((uint32_t) data[0]);
}

void HX711::setOffset(long offset)
{
  _offset = offset;
}

void HX711::setScale(float scale)
{
  _scale = scale;
}

float HX711::getGrams(byte times)
{
  long val = (averageValue(times) - _offset);
  return (float) val/_scale;
}