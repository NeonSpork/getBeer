#include "./include/App.hpp"
#include <wiringPi.h>

int main(int argc, char const *argv[])
{
  // Must be called at beginning of program to function correctly
  wiringPiSetupGpio();
  std::cout << "wiringPi complete";
  
  App getBeer;
  getBeer.run();
  return 0;
}