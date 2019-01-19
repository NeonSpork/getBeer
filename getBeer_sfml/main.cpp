#include "./include/App.hpp"

int main(int argc, char const *argv[])
{
  // Must be called at beginning of program to function correctly
  wiringPiSetup();
  pinMode(29, OUTPUT); // Beer valve
  pinMode(31, OUTPUT); // Secret valve
  // HX711 hx = Pint::initializeHX(hx, 2, 3);
  // Pint pint();
  App getBeer;
  getBeer.run();
  return 0;
}
