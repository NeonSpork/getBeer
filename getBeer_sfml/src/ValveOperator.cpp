#include "../include/ValveOperator.hpp"

ValveOperator::ValveOperator()
: beerDispensing{false}
, secretDispensing{false}
{
  Valve beer(5);
  Valve secret(6);
}

void ValveOperator::beerValve(bool state)
{
  // GPIO::DigitalOut beer(beerPin);
  if (state)
  {
    beer.on();  
  }
  if (!state)
  {
    beer.off();
  }
  beerDispensing = state;
}
void ValveOperator::secretValve(bool state)
{
  // GPIO::DigitalOut secret(secretPin);
  if (state)
  {
    secret.on();  
  }
  if (!state)
  {
    secret.off();
  }
  secretDispensing = state;
}

bool ValveOperator::getBeerStatus()
{
  return beerDispensing;
}

bool ValveOperator::getSecretStatus()
{
  return secretDispensing;
}
