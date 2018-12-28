//World.cpp
#include "../include/ActiveBeer.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <algorithm>
#include <cmath>

ActiveBeer::ActiveBeer(sf::RenderWindow& window)
: mWindow(window)
, mTextures()
, mSceneGraph()
, mSceneLayers()
, mNormalValve(Valve::Type::Normal, 5)
, mSecretValve(Valve::Type::Secret, 6)
// DON'T FORGET ABOUT BUTTONS AND PINT NUMBERS AND STUFF
{
  loadTextures();
  buildScene();
}

void ActiveBeer::update(sf::Time deltaTime)
{
  // Forward commands to scene graph, and adapt status of valves etc
  while (!mCommandQueue.isEmpty())
    mSceneGraph.onCommand(mCommandQueue.pop(), deltaTime);
  adaptDispenserStatus();
  mSceneGraph.update(deltaTime);
}

void ActiveBeer::draw()
{
  mWindow.draw(mSceneGraph);
}

CommandQueue& ActiveBeer::getCommandQueue()
{
  return mCommandQueue;
}

void ActiveBeer::loadTextures()
{
  // Backgrounds
  mTextures.load(Textures::default_background, "media/bg/default_background.png");
  mTextures.load(Textures::tropical_thunder_bg, "media/bg/tropical_thunder_bg.png");
  mTextures.load(Textures::angry_babushka_bg, "media/bg/angry_babushka_bg.png");
  mTextures.load(Textures::brick_wall, "media/bg/brick_wall.png");
  // Icons
  mTextures.load(Textures::angry_babushka_icon, "media/icon/angry_babushka_icon.png");
  mTextures.load(Textures::beer_button_off, "media/icon/beer_button_off.png");
  mTextures.load(Textures::beer_button_on, "media/icon/beer_button_on.png");
  mTextures.load(Textures::beer_button_red_off, "media/icon/beer_button_red_off.png");
  mTextures.load(Textures::beer_button_red_on, "media/icon/beer_button_red_on.png");
  mTextures.load(Textures::coming_soon_icon, "media/icon/coming_soon_icon.png");
  // mTextures.load(Textures::cursor, "media/icon/cursor.png");
  mTextures.load(Textures::default_icon, "media/icon/default_icon.png");
  mTextures.load(Textures::exit, "media/icon/exit.png");
  mTextures.load(Textures::ml_icon, "media/icon/ml_icon.png");
  mTextures.load(Textures::pints, "media/icon/pints.png");
  mTextures.load(Textures::secret_off, "media/icon/secret_off.png");
  mTextures.load(Textures::secret_on, "media/icon/secret_on.png");
  mTextures.load(Textures::temp_icon, "media/icon/temp_icon.png");
  mTextures.load(Textures::tropical_thunder_icon, "media/icon/tropical_thunder_icon.png");
  // Number images
  mTextures.load(Textures::num0, "media/num/num0.png");
  mTextures.load(Textures::num1, "media/num/num1.png");
  mTextures.load(Textures::num2, "media/num/num2.png");
  mTextures.load(Textures::num3, "media/num/num3.png");
  mTextures.load(Textures::num4, "media/num/num4.png");
  mTextures.load(Textures::num5, "media/num/num5.png");
  mTextures.load(Textures::num6, "media/num/num6.png");
  mTextures.load(Textures::num7, "media/num/num7.png");
  mTextures.load(Textures::num8, "media/num/num8.png");
  mTextures.load(Textures::num9, "media/num/num9.png");
}

void ActiveBeer::adaptDispenserStatus()
{
  // Should adjust valve to open or shut depending on button state
  mNormalValve.setStatus()
}