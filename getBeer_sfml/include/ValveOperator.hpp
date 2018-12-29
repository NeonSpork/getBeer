#ifndef VALVEOPERATOR_HPP
#define VALVEOPERATOR_HPP

#include "Valve.hpp"

class ValveOperator
{
public:
  ValveOperator();
  ~ValveOperator(){};
  void beerValve(bool on);
  void secretValve(bool on);
  bool getBeerStatus();
  bool getSecretStatus();
private:
  Valve beer(5);
  Valve secret(6);
  bool beerDispensing;
  bool secretDispensing;
};

#endif // VALVEOPERATOR_HPP