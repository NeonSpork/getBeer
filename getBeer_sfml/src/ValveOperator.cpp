#include "../include/ValveOperator.hpp"

ValveOperator::ValveOperator()
: beerDispensing{false}
, secretDispensing{false}
{}

void ValveOperator::openValve(const GPIO::DigitalOut &valve, char name, bool state)
{
  if (state)
  {
    valve.on();
  }
  if (!state)
  {
    valve.off();
  }
  switch (name)
  {
    case 'b':
      beerDispensing = state;
      break;
    case 's':
      secretDispensing = state;
      break;
    default:
      std::cout << "Valve error: Invalid name, cannot set status.";
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
