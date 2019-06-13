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
    std::cout << "SensorFail error, check HX711 wiring.\n";
    return 99;
  }
  catch (std::exception& e)
  {
    std::cout << "Unexpected HX711 error: " << e.what();
    return 88;
  }
} 

float Sensor::checkTemp()
{
  // try
  // {
  //   float tempC = temp.getTemp();
  //   std::cout << "Sensor::checkTemp(): " << tempC << std::endl;
  //   return tempC;
  // }
  // catch (std::exception& e)
  // {
  //   std::cout << "Unexpected HX711 error: " << e.what();
  //   return 99;
  // }
  return 88;
}