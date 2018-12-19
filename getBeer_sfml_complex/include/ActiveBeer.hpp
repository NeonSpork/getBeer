// World.hpp
#ifndef ACTIVEBEER_HPP
#define ACTIVEBEER_HPP

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "SpriteNode.hpp"
#include "Valve.hpp"
#include "CommandQueue.hpp"
#include "Command.hpp"
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <array>
#include <queue>

// Forward declaration
namespace sf
{
  class RenderWindow;
}

class ActiveBeer : private sf::NonCopyable
{
public:
  explicit ActiveBeer(sf::RenderWindow& window);
  void update(sf::Time deltaTime);
  void draw();
  CommandQueue& getCommandQueue();
private:
  void loadTextures();
  void buildScene();
  void adaptDispenserStatus();
  enum Background
  {
    DefaultBackground,
    AngryBabushka,
    TropicalThunder,
    BrickWall,
    BackgroundCount
  };
  sf::RenderWindow& mWindow;
  TextureHolder mTextures;
  SceneNode mSceneGraph;
  std::array<SceneNode*, BackgroundCount> mSceneLayers;
  CommandQueue mCommandQueue;
  Valve mNormalValve;
  Valve mSecretValve;
  // DON'T FORGET ABOUT THE BUTTONS AND PINT NUMBERS
};

#endif