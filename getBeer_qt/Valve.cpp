#include "Valve.hpp"

Valve::Valve(unsigned int pinNumber)
: mIsOpen(false)
, mPin(pinNumber)
{
    mValve(mPin);
    shutValve();
}

void Valve::openValve()
{
    mValve.on();
    mIsOpen = true;
}

void Valve::shutValve()
{
    mValve.off();
    mIsOpen = false;
}

bool Valve::isValveOpen()
{
    return mIsOpen;
}
