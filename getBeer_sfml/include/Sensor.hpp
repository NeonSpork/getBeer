#ifndef SENSOR_HPP
#define SENSOR_HPP

#include "hx711.h"
// #include "ds18b20.h"

class App;

class Sensor
{
public:
  Sensor();
  int checkWeight();
  float checkTemp();
  class SensorFail{};
private:
  HX711 hx;
  // Ds18b20 temp;
};

#endif