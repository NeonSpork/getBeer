#ifndef APP_HPP
#define APP_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "StateIdentifiers.hpp"
#include "ValveOperator.hpp"
#include "Sensor.hpp"

class Sensor;

class App
{
public:
  App();
  ~App();
  void run();
  static constexpr int wWidth{1024};
  static constexpr int wHeight{600};
  static constexpr float xRel{1};
  static constexpr float yRel{1};
private:
  sf::RenderWindow mWindow;
  TextureHolder mTextures;
  sf::Sprite mBackground;
  sf::Sprite mButtonOff;
  sf::Sprite mButtonOn;
  sf::Sprite mXicon;
  sf::Sprite mSecretIconOn;
  sf::Sprite mIcon0;
  sf::Sprite mIcon1;
  sf::Sprite mIcon2;
  sf::Sprite mIcon3;
  sf::Sprite mIcon4;
  sf::Sprite mIcon5;
  sf::Sprite mIcon6;
  sf::Sprite mIcon7;
  sf::Sprite mIcon8;
  sf::Sprite mIcon9;
  sf::Sprite mIcon10;
  sf::Sprite mIcon11;
  sf::Sprite mIcon12;
  ValveOperator vo;
  Sensor sensor;
  int mPints;
  int mTemp;
  int checkPints();
  int checkTemp();

  State::ID mState;
  State::ID mOldState;
  bool mNewButtonState;
  bool mOldButtonState;
  bool mNewSecretState;
  bool mOldSecretState;

  const sf::Time TimePerFrame;
  void events();
  void update(const sf::Time& TimePerFrame);
  void render();
  void handleInput(sf::Keyboard::Key key, bool isPressed);
  void handleInput(sf::Mouse::Button button, bool isPressed);
  void handleInput(unsigned int touch, bool isPressed);
  void swipe(int oldX, int newX);
  void setState(State::ID name);
  void loadTextures();
  void placeTextures();

  // FPS and TimePerFrame display, will be removed in final version
  void updateStatistics(sf::Time elapsedTime);
  sf::Font mFont;
  sf::Text mStatisticsText;
  sf::Time mStatisticsUpdateTime;
  std::size_t mStatisticsNumFrames;
};



#endif // APP_HPP
