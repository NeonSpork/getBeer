#include "../include/Valve.hpp"
#include <cmath>

Valve::Valve(unsigned int pin)
: mValvePin{GPIO::DigitalOut(pin)}
{
  // Valve GPIO pin starts closed
  mValvePin.off();
}
