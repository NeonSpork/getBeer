#ifndef VALVEOPERATOR_HPP
#define VALVEOPERATOR_HPP

#include <string>
#include <cppgpio.hpp>

namespace Valve
{
  static constexpr unsigned int beerPin = 5;
  static const GPIO::DigitalOut beer(beerPin);
  static constexpr unsigned int secretPin = 6;
  static const GPIO::DigitalOut secret(secretPin);
}

class ValveOperator
{
public:
  ValveOperator();
  ~ValveOperator(){};
  void openValve(char name, bool state);
  bool getBeerStatus();
  bool getSecretStatus();
private:
  bool beerDispensing;
  bool secretDispensing;
};

#endif // VALVEOPERATOR_HPP