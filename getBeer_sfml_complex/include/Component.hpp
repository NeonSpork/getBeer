#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <memory>

namespace sf
{
  class Event;
  class RenderWindow;
}

namespace GUI
{

class Component : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public:
  typedef std::shared_ptr<Component> Ptr;
  Component();
  virtual ~Component();
  virtual bool isActive() const;
  virtual void activate();
  virtual void deactivate();
  virtual void handleEvent(const sf::Event& event) = 0;
private:
  bool mIsActive;
};

}

#endif //COMPONENT_HPP