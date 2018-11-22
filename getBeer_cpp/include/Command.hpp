#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Category.hpp"
#include <SFML/System/Time.hpp>
#include <functional>
#include <cassert>

class SceneNode;

struct Command
{
  Command();
  std::function<void(SceneNode&, sf::Time)> action;
  unsigned int category;
};

template <typename DispenserObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn)
{
  return [=] (SceneNode& node, sf::Time deltaTime)
  {
    // Check for cast safety
    assert(dynamic_cast<DispenserObject*>(&node) != nullptr);
    // Downcast node and invoke function on it
    fn(static_cast<DispenserObject&>(node), deltaTime);
  };
}

#endif