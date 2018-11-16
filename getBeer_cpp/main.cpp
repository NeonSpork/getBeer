// getBeer
//
// A framework for a custom beer dispenser and kegerator
// running on a Raspberry Pi, a touch screen, a bunch of
// electronics and an old fridge.

#include "./include/App.hpp"
#include <stdexcept>
#include <iostream>

int main()
{
  try
  {
    App getBeer;
    getBeer.run();
  }
  catch (std::exception& e)
  {
    std::cout << "\nEXCEPTION:" << e.what();
  }
  return 0;
}