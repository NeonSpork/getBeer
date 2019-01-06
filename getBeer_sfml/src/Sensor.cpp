#include "../include/Sensor.hpp"

Sensor::Sensor()
: hx(2, 3)
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