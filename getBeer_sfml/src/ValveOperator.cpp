#include "../include/ValveOperator.hpp"

ValveOperator::ValveOperator()
: beerDispensing{false}
, secretDispensing{false}
{
  pinMode(beerpin, OUTPUT); // Beer valve
  pinMode(secretpin, OUTPUT); // Secret valve
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
<<<<<<< HEAD
      digitalWrite(31, state);
=======
      digitalWrite(secretpin, state);
>>>>>>> b21dee48a4eb2f47c6f521462cb1e17c95d2332d
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
