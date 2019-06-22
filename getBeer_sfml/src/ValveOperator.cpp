#include "../include/ValveOperator.hpp"

ValveOperator::ValveOperator()
: beerDispensing{false}
, secretDispensing{false}
{
  pinMode(21, OUTPUT); // Beer valve
  pinMode(22, OUTPUT); // Secret valve
  digitalWrite(21, false);
  digitalWrite(22, false);
}

ValveOperator::~ValveOperator()
{
  digitalWrite(21, false);
  digitalWrite(22, false);
}

void ValveOperator::openValve(char name, bool state)
{
  switch (name)
  {
    case 'b':
      digitalWrite(21, state);
      beerDispensing = state;
      break;
    case 's':
      digitalWrite(22, state);
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
