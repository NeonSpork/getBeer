#include "./include/App.hpp"
#include "../getBeer_Qt/CppGPIO/include/cppgpio/output.hpp"

int main(int argc, char const *argv[])
{
  App getBeer;
  getBeer.run();
  return 0;
}