#ifndef VALVE_HPP
#define VALVE_HPP

#include <cppgpio.hpp>

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
  // static const int beerPin = 5;
  // static const int secretPin = 6;
  // GPIO::DigitalOut beerGPIO(beerPin);
  // GPIO::DigitalOut secretGPIO(secretPin);
  bool beerDispensing;
  bool secretDispensing;
};

#endif