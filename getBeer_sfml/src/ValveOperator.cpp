#include "../include/ValveOperator.hpp"

ValveOperator::ValveOperator()
: beerDispensing{false}
, secretDispensing{false}
{
  pinMode(5, OUTPUT); // Beer valve
  pinMode(6, OUTPUT); // Secret valve
  digitalWrite(5, false);
  digitalWrite(6, false);
}

ValveOperator::~ValveOperator()
{
  digitalWrite(5, false);
  digitalWrite(6, false);
}

void ValveOperator::openValve(char name, bool state)
{
  switch (name)
  {
    case 'b':
      digitalWrite(5, state);
      beerDispensing = state;
      break;
    case 's':
      digitalWrite(6, state);
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
