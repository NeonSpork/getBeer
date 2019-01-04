#include "../include/PintConverter.hpp"


Pint::Pint()
{
  HX711 hx(dout, slk);
}

int Pint::calculate()
{
  int dryWeight = 4025;
  int wetWeight = (int) hx.getGrams();
  return ((wetWeight-dryWeight)/500);
}
