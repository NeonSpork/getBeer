#include "../include/Sensor.hpp"

Sensor::Sensor()
: hx(3, 5)
{

}

int Sensor::checkWeight()
{
  int dryWeight = 4025;
  int wetWeight = hx.getGrams();
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