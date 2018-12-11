#ifndef VALVE_HPP
#define VALVE_HPP

#include <wiringPi.h>

class Valve
{
public:
    Valve(int pinNumber);
    ~Valve(){}
    void on();
    void off();
    bool isOpen();
private:
    const int mPin;
    bool status;
};

#endif // VALVE_HPP
