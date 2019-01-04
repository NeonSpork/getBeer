#include "../include/PintConverter.hpp"

namespace Pint
{
  HX711 initializeHX(name)
  {
    HX711 name(2, 3);
    return name;
  }

  int calculate()
  {
    int dryWeight = 4025;
    int wetWeight = (int) hx.getGrams();
    return ((wetWeight-dryWeight)/500);
  }
}
