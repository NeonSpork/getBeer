#include "../include/Valve.hpp"
#include <cmath>

Valve::Valve(Type type, GPIO::DigitalOut valvepin)
: mType(type)
, mValvePin(valvepin)
, mIsOpen(false)
{
  // Valve GPIO pin starts closed

  mValvePin.off()
}