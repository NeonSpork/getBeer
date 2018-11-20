// Player.cpp
#include "../include/BeerDrinker.hpp"
#include "../include/CommandQueue.hpp"
#include "../include/Valve.hpp"
#include "../include/Foreach.hpp"
#include <map>
#include <string>
#include <algorithm>

struct ValveOperator
{
  ValveOperator(GPIO::DigitalOut valveName, int GPIOpin)
  : GPIO::DigitalOut normalValve(10)
  {

  }
};