#ifndef VALVE_HPP
#define VALVE_HPP

#include <cppgpio.hpp>

class Valve : protected GPIO::DigitalOut
{
public:
  Valve();
private:
  const int mPin;
};

#endif // VALVE_HPP