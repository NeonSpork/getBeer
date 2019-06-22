#include "../include/ValveOperator.hpp"

ValveOperator::ValveOperator()
: beerDispensing{false}
, secretDispensing{false}
{
  pinMode(beerpin, OUTPUT); // Beer valve
  pullUpDnControl (beerpin, PUD_DOWN);
  pinMode(secretpin, OUTPUT); // Secret valve
  pullUpDnControl (secretpin, PUD_DOWN);
  digitalWrite(beerpin, false);
  digitalWrite(secretpin, false);
}

ValveOperator::~ValveOperator()
{
  digitalWrite(beerpin, false);
  digitalWrite(secretpin, false);
}

void ValveOperator::openValve(char name, bool state)
{
  switch (name)
  {
    case 'b':
      digitalWrite(beerpin, state);
      beerDispensing = state;
      break;
    case 's':
      digitalWrite(secretpin, state);
      secretDispensing = state;
      break;
    default:
      std::cout << "Valve error: Invalid name. Correct name is 'b' or 's' (for beer or secret)\n";
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
