#include "../include/ValveOperator.hpp"

ValveOperator::ValveOperator()
: beerDispensing{false}
, secretDispensing{false}
{}

void ValveOperator::openValve(const GPIO::DigitalOut &valve, bool state)
{
  if (state)
  {
    valve.on();
  }
  if (!state)
  {
    valve.off();
  }
}

void ValveOperator::status(char name, bool state)
{
  switch (name)
  {
    case 'b':
      beerDispensing = state;
      break;
    case 's':
      secretDispensing = state;
      break;
  }
}

bool ValveOperator::getBeerStatus()
{
  return beerDispensing;
}

bool ValveOperator::getSecretStatus()
{
  return secretDispensing;
}
