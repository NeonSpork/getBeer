#include "../include/Valve.hpp"
#include <cmath>

Valve::Valve(Type type, unsigned int pin)
: mType(type)
, mPin(pin)
, mIsOpen(false)
{
  // Valve GPIO pin starts closed
  mValvePin(mPin);
}