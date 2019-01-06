#ifndef VALVEOPERATOR_HPP
#define VALVEOPERATOR_HPP

#include <iostream>
#include <wiringPi.h>


class ValveOperator
{
public:
  ValveOperator();
  ~ValveOperator();
  void openValve(char name, bool state);
  bool getBeerStatus();
  bool getSecretStatus();
private:
  bool beerDispensing;
  bool secretDispensing;
};

#endif // VALVEOPERATOR_HPP