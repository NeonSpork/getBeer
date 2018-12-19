#ifndef STATE_HPP
#define STATE_HPP

#include "StateIdentifiers.hpp"
#include "ResourceIdentifiers.hpp"
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>

namespace sf
{
  class RenderWindow;
}

class StateStack;
class BeerDrinker;

class State
{
public:
  typedef std::unique_ptr<State> Ptr;
  struct Context
  {
    Context(sf::RenderWindow& window, TextureHolder& textures, BeerDrinker& beerdrinker);
    sf::RenderWindow* window;
    TextureHolder* textures;
    BeerDrinker* beerdrinker;

  };

public:
  State(StateStack& stack, Context context);
  virtual ~State();
  virtual void draw() = 0;
  virtual bool update(sf::Time deltatime) = 0;
  virtual bool handleEvent(const sf::Event& event) = 0;
  virtual void onActivate();
  virtual void onDestroy();

protected:
  void requestStackPush(States::ID stateID);
  void requestStackPop();
  void requestStateClear();
  Context getContext() const;

private:
  StateStack* mStack;
  Context mContext;
};

#endif // STATE_HPP