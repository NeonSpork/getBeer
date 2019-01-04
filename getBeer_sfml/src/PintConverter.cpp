#include "../include/PintConverter.hpp"

namespace Pint
{
  HX711 initializeHX(HX711 name, unsigned int dout, unsigned int slk)
  {
    HX711 name(dout, slk);
    return name;
  }

  int calculate()
  {
    int dryWeight = 4025;
    int wetWeight = (int) hx.getGrams();
    return ((wetWeight-dryWeight)/500);
  }
}
