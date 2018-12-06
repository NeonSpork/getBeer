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
}

void Valve::shutValve()
{
    mValve.off();

bool Valve::isValveOpen()
{
    return mIsOpen;
}
