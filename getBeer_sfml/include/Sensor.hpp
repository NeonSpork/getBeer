#ifndef SENSOR_HPP
#define SENSOR_HPP

#include "hx711.h"
// #include "TEMPSENSOR"

class App;

class Sensor
{
public:
  Sensor();
  int checkWeight();
  // float checkTemp();
private:
  HX711 hx;
  // static const TEMPSENSOR temp;
};

#endif