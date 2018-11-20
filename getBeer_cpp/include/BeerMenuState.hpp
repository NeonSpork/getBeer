//MenuState.hpp
#ifndef BEERMENUSTATE_HPP
#define BEERMENUSTATE_HPP

#include "State.hpp"
#include "Container.hpp"
#include <SFML/Graphics/Sprite.hpp>

class BeerMenuState : public State
{
public:
  BeerMenuState(StateStack& stack, Context context);
  virtual void draw();
  virtual bool update(sf::Time deltaTime);
  virtual bool handleEvent(const sf::Event& event);
private:
  sf::Sprite mBackgroundSprite;
  GUI::Container mGUIContainer;
};

#endif