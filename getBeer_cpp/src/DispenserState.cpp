#include "../include/DispenserState.hpp"

DispenserState::DispenserState(StateStack& stack, Context context)
: State(stack, context)
, mActiveBeer(*context.window)
, mBeerDrinker(*context.beerdrinker)
{}

void DispenserState::draw()
{
  mActiveBeer.draw();
}

bool DispenserState::update(sf::Time deltaTime)
{
  mActiveBeer.update(deltaTime);
  CommandQueue& commands = mActiveBeer.getCommandQueue();
  mBeerDrinker.handleRealtimeInput(commands);
  return true;
}

bool DispenserState::handleEvent(const sf::Event& event)
{
  // Dinspenser input handling
  CommandQueue& commands = mActiveBeer.getCommandQueue();
  mBeerDrinker.handleEvent(event, commands);

  // Escape pressed, trigger exit from program
  if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    requestStackPush(States::None);
  return true;
}