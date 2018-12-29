#ifndef VALVE_HPP
#define VALVE_HPP

#include "../../getBeer_Qt/CppGPIO/include/cppgpio/gpio.hpp"

class Valve
{
friend class GPIO::DigitalOut;
public:
  Valve();
private:
  const int mPin;
};

#endif // VALVE_HPP