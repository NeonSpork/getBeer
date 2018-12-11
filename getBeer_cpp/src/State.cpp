#include "../include/State.hpp"
#include "../include/StateStack.hpp"

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, BeerDrinker& beerdrinker)
: window(&window)
, textures(&textures)
, beerdrinker(&beerdrinker)
{
}

State::State(StateStack& stack, Context context)
: mStack(&stack)
, mContext(context)
{
}

State::~State()
{
}

void State::requestStackPush(States::ID stateID)
{
  mStack->pushState(stateID);
}

void State::requestStackPop()
{
  mStack->popState();
}

void State::requestStateClear()
{
  mStack->clearStates();
}

State::Context State::getContext() const
{
  return mContext;
}

void State::onActivate()
{
}

void State::onDestroy()
{
}