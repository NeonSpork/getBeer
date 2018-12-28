#ifndef VALVE_HPP
#define VALVE_HPP

#include <string>
#include <cppgpio.hpp>

class ValveOperator
{
public:
  ValveOperator();
  ~ValveOperator(){};
  void beerValve(bool on);
  void secretValve(bool on);
  bool getState(std::string name);
private:
  static const int beerPin = 5;
  static const int secretPin = 6;
  // GPIO::DigitalOut beerGPIO;
  // GPIO::DigitalOut secretGPIO;
  bool beerDispensing;
  bool secretDispensing;
};

#endif