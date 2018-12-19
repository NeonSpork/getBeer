#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "Component.hpp"
#include <vector>
#include <memory>

namespace GUI
{
  
class Container : public Component
{
public:
  typedef std::shared_ptr<Container> Ptr;
  Container();
  void pack(Component::Ptr component);
  virtual void handleEvent(const sf::Event& event);
private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  std::vector<Component::Ptr> mChildren;
};

}

#endif