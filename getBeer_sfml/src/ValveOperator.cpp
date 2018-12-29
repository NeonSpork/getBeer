#include "../include/ValveOperator.hpp"

struct Valve
{
  static constexpr int beerPin{5};
  static constexpr int secretPin{6};
  GPIO::DigitalOut beer(int beerPin);
  GPIO::DigitalOut secret(int secretPin);
};

ValveOperator::ValveOperator()
: beerDispensing{false}
, secretDispensing{false}
{
  // beerGPIO(5);
  // secretGPIO(6);
}

void ValveOperator::beerValve(bool on)
{
  // GPIO::DigitalOut beer(beerPin);
  if (on)
  {
    Valve::beer.on();  
  }
  if (!on)
  {
    Valve::beer.off();
  }
  beerDispensing = on;
}
void ValveOperator::secretValve(bool on)
{
  // GPIO::DigitalOut secret(secretPin);
  if (on)
  {
    Valve::secret.on();  
  }
  if (!on)
  {
    Valve::secret.off();
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
