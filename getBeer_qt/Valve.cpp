#include <Valve.hpp>

Valve::Valve(int pinNumber)
: mPin(pinNumber)
, status(false)
{
    pinMode(mPin, OUTPUT);
}

void Valve::on()
{
    digitalWrite(mPin, HIGH);
    status = true;
}

void Valve::off()
{
    digitalWrite(mPin, LOW);
    status = false;
}

bool Valve::isOpen()
{
    return status;
}
