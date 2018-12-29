#ifndef VALVE_HPP
#define VALVE_HPP

#include <cppgpio.hpp>

class Valve
{
friend class GPIO::DigitalOut;
public:
  explicit Valve(int pin);
private:
  const int mPin;
};

#endif // VALVE_HPP