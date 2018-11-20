// GameState.hpp
#ifndef DISPENSERSTATE_HPP
#define DISPENSERSTATE_HPP

#include "State.hpp"
#include "ActiveBeer.hpp"
#include "BeerDrinker.hpp"
#include <SFML/Graphics/Sprite.hpp>

class DispenserState : public State
{
  public:
    DispenserState(StateStack& stack, Context context);
    virtual void draw();
    virtual bool update(sf::Time deltaTime);
    virtual bool handleEvent(const sf::Event& event);
  private:
    ActiveBeer mActiveBeer;
    BeerDrinker mBeerDrinker;
};

#endif