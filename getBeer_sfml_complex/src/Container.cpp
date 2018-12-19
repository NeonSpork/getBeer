#include "../include/Container.hpp"
#include "../include/Foreach.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace GUI
{

Container::Container()
: mChildren()
{}

void Container::pack(Component::Ptr component)
{
  mChildren.push_back(component);
}

void Container::handleEvent(const sf::Event& event)
{
  if (event.type == sf::Event::MouseButtonPressed)
  {
    // Check if mouse is over button

  }
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  FOREACH(const Component::Ptr& child, mChildren)
          target.draw(*child, states);
}

}