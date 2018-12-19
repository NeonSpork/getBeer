//Aircraft.hpp
#ifndef VALVE_HPP
#define VALVE_HPP

#include "Entity.hpp"
#include "CommandQueue.hpp"
#include <cppgpio.hpp>


class Valve : public Entity
{
public:
  Valve(unsigned int pin);
  virtual unsigned int getCategory() const;
private:
  // functions to open and close valves
  virtual void updateCurrent(sf::Time deltaTime, CommandQueue& commands);
  GPIO::DigitalOut mValvePin;
  Command mOpen;
  Command mClose;
  bool mIsOpen;
};

#endif