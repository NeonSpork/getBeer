#include "../include/ValveOperator.hpp"

ValveOperator::ValveOperator()
: beerDispensing{false}
, secretDispensing{false}
{
  // beerGPIO(5);
  // secretGPIO(6);
}

void ValveOperator::beerValve(bool on)
{
  GPIO::DigitalOut beer(beerPin);
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
  GPIO::DigitalOut secret(secretPin);
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

bool ValveOperator::getState(std::string name)
{
  if (name == "beer")
  {
    return beerDispensing;
  }
  if (name == "secret")
  {
    return secretDispensing;
  }
  else
  {
    return false;
  }
}