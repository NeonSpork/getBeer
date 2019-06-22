#include <iostream>
#include "hx711.h"


int getInt()
{
  int n = 0;
  while (true)
  {
    if (std::cin >> n) return n;
    std::cout << "Invalid format, please enter value as INTEGER.\n";
  }
}

int main(int argc, char const *argv[])
{
  wiringPiSetup();

  HX711 hx(8, 9);
  long averageVal = hx.averageValue();
  hx.setOffset(averageVal);
  char cont = 'a';
  std::cout << "!!!!! Remove all items from scale !!!!!\nress any key to continue.\n";
  std::cin >> cont;
  long offset = hx.getOffset();
  std::cout << "Place item with known weight on scale.\nPress any key to continue.\n";
  std::cin >> cont;
  long averageValItem = hx.averageValue() - offset;
  std::cout << "Bitvalue of weighed item (minus offset): " << averageValItem << std::endl;
  std::cout << "Input exact weight of item in grams as an integer.\n> ";
  int reportedWeight = getInt();
  float scale = averageValItem/reportedWeight;
  hx.setScale(scale);
  std::cout << "\n\n#########################################\n";
  std::cout << "\n#########################################\n";
  std::cout << "\n### Offset: " << offset << std::endl;
  std::cout << "\n#########################################\n";
  std::cout << "\n### Scale:  " << scale << std::endl;
  std::cout << "\n#########################################\n";
  std::cout << "\n############## Terminating. #############\n";
  return 0;
}