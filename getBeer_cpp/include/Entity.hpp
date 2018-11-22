#ifndef ENTITY_HPP
#define ENTITY_HPP
// Class for various hardware such as valves

#include "SceneNode.hpp"

class Entity : public SceneNode
{
public:
  void setValveStatus(int GPIO);
  void updateTemperature();
  void pushInfoToLCD();
private:
  virtual void updateCurrent(sf::Time deltaTime);
  bool mValveIsOpen(int GPIO);
};


#endif