#include "../include/Sensor.hpp"

Sensor::Sensor()
: hx(3, 5)
, temp()
{

}

int Sensor::checkWeight()
{
  try
  {
    int dryWeight = 4025;
    int wetWeight = hx.getGrams();
    if (wetWeight == -999999.)
    {
      throw SensorFail{};
    }
    int beerWeight = wetWeight-dryWeight;
    if (beerWeight > 0)
    {
      return beerWeight;
    }
    else
    {
      return 0;
    }
  }
  catch (SensorFail)
  {
    std::cout << "HX711 not working.\n";
    return 99;
  }
} 

float Sensor::checkTemp()
{
  float tempC = temp.getTemp();
  std::cout << "Sensor::checkTemp(): " << tempC << std::endl;
  return tempC;
}