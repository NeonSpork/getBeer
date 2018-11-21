#ifndef VALVE_HPP
#define VALVE_HPP

#include <cppgpio.hpp>

class Valve
{
public:
    Valve(unsigned int pinNumber);
    void openValve();
    void shutValve();
    bool isValveOpen();
private:
    bool mIsOpen;
    unsigned int mPin;
    GPIO::DigitalOut static mValve(unsigned int pinNumber);
};

#endif // VALVE_HPP
