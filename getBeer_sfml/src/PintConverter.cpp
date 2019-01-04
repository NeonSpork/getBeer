#include "../include/PintConverter.hpp"
// wiringPiSetupGpio();
namespace Pint
{
  HX711 hx(2, 3);

  int calculate()
  {
    int dryWeight = 4025;
    int wetWeight = (int) hx.getGrams();
    return ((wetWeight-dryWeight)/500);
  }
}
