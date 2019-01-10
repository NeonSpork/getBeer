#include <Python.h>
#include "./include/App.hpp"
#include <wiringPi.h>

int main(int argc, char const *argv[])
{
  // Must be called at beginning of program to function correctly
  wiringPiSetupGpio();
  Py_Initialize(); 
  App getBeer;
  getBeer.run();
  Py_Finalize();
  return 0;
}