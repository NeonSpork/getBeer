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

void ValveOperator::openValve(char name, bool state)
  // \brief Sets the state of valve to open (true) or closed (false)
  // \param name 'b' for beer valve or 's' for secret valve
  // \param state true or false
{
  const GPIO::DigitalOut *valve;
  switch (name)
  {
    case 'b':
      valve = &Valve::beer;
      beerDispensing = state;
      break;
    case 's':
      valve = &Valve::secret;
      secretDispensing = state;
      break;
  }
  if (state)
  {
    valve->on();
  }
  if (!state)
  {
    valve->off();
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
