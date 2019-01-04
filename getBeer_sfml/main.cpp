#include "./include/App.hpp"

int main(int argc, char const *argv[])
{
  // Must be called at beginning of program to function correctly
  wiringPiSetupGpio();
  pinMode(5, OUTPUT); // Beer valve
  pinMode(6, OUTPUT); // Secret valve
  HX711 hx = Pint::initializeHX(hx, 2, 3);

  App getBeer;
  getBeer.run();
  return 0;
}
