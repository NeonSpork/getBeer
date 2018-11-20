#include "../include/StateStack.hpp"
#include "../include/Foreach.hpp"

#include <cassert>

StateStack::StateStack(State::Context context)
: mStack()
, mPendingList()
, mContext(context)
, mFactories()
{
}

void StateStack::update(sf::Time deltaTime)
{
  // Iterates from top tp bottom, stops when update() returns false
  for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
  {
    if (!(*itr)->update(deltaTime))
      break;
  }
  applyPendingChanges();
}

void StateStack::draw()
{
  // Draw all actove states from bottom to top
  FOREACH(State::Ptr& state, mStack)
          state->draw();
}

void StateStack::handleEvent(const sf::Event& event)
{
  // iterate from top tp bottom, stop as soon as handleEvent() returns false
  for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
  {
    if (!(*itr)->handleEvent(event))
      break;
  }
  applyPendingChanges();
}

void StateStack::pushState(States::ID stateID)
{
  mPendingList.push_back(PendingChange(Push, stateID));
}

void StateStack::popState()
{
  mPendingList.push_back(PendingChange(Pop));
}

void StateStack::clearStates()
{
  mPendingList.push_back(PendingChange(Clear));
}

bool StateStack::isEmpty() const
{
  return mStack.empty();
}

State::Ptr StateStack::createState(States::ID stateID)
{
  auto found = mFactories.find(stateID);
  assert(found != mFactories.end());
  return found->second();
}

void StateStack::applyPendingChanges()
{
  FOREACH(PendingChange change, mPendingList)
  {
    switch (change.action)
    {
      case Push:
        mStack.push_back(createState(change.stateID));
        break;
      case Pop:
        mStack.pop_back();
        break;
      case Clear:
        mStack.clear();
        break;
    }
  }
  mPendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
: action(action)
, stateID(stateID)
{}