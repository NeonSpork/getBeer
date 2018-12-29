#include "../include/ValveOperator.hpp"

ValveOperator::ValveOperator()
: beerDispensing{false}
, secretDispensing{false}
{
  beer.off();
  secret.off();
}

void ValveOperator::beerValve(bool on)
{
  // GPIO::DigitalOut beer(beerPin);
  if (on)
  {
    beer.on();  
  }
  if (!on)
  {
    beer.off();
  }
  beerDispensing = on;
}
void ValveOperator::secretValve(bool on)
{
  // GPIO::DigitalOut secret(secretPin);
  if (on)
  {
    secret.on();  
  }
  if (!on)
  {
    secret.off();
  }
  secretDispensing = on;
}

bool ValveOperator::getBeerStatus()
{
  return beerDispensing;
}

bool ValveOperator::getSecretStatus()
{
  return secretDispensing;
}
