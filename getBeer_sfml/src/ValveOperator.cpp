#include "../include/ValveOperator.hpp"

ValveOperator::ValveOperator()
: beerDispensing{false}
, secretDispensing{false}
{
  pinMode(29, OUTPUT); // Beer valve
  pinMode(31, OUTPUT); // Secret valve
  digitalWrite(29, false);
  digitalWrite(31, false);
}

ValveOperator::~ValveOperator()
{
  digitalWrite(29, false);
  digitalWrite(31, false);
}

void ValveOperator::openValve(char name, bool state)
{
  switch (name)
  {
    case 'b':
      digitalWrite(29, state);
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
