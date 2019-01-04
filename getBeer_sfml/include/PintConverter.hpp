#include "hx711.h"

class Pint
{
public:
  Pint();
private:
  HX711 hx(unsigned int dout, unsigned int slk);
  static const unsigned int dout{2};
  static const unsigned int slk{3};
  int calculate();
}
