// "Player.hpp"
#ifndef BEERDRINKER_HPP
#define BEERDRINKER_HPP

#include "Command.hpp"
#include <SFML/Window/Event.hpp>
#include <map>

class CommandQueue;

class BeerDrinker
{
public:
  enum Action
  {
    DrinkBeer,
    DrinkSecret,
    ActionCount
  };
  BeerDrinker();
  void handleEvent(const sf::Event& event, CommandQueue commands);
  void handleRealtimeInput(CommandQueue& commands);
private:
  void initializeActions();
  static bool isRealtimeAction(Action action);
  std::map<Action, Command> mActionBinding;
};

#endif