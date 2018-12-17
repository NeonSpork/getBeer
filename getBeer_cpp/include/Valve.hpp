//Aircraft.hpp
#ifndef VALVE_HPP
#define VALVE_HPP

#include "Entity.hpp"
#include "CommandQueue.hpp"
#include <cppgpio.hpp>


class Valve : public Entity
{
public:
  enum Type
  {
    Normal,
    Secret,
  };
  Valve(Type type, unsigned int mPin){};
  virtual unsigned int getCategory() const;
private:
  // functions to open and close valves
  virtual void updateCurrent(sf::Time deltaTime, CommandQueue& commands);
  Type mType;
  unsigned int mPin;
  GPIO::DigitalOut mValvePin(int pinNumber);
  Command mOpen;
  Command mClose;
  bool mIsOpen;
};

#endif