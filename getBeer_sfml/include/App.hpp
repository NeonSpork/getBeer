#ifndef APP_HPP
#define APP_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "StateIdentifiers.hpp"
#include "ValveOperator.hpp"
#include "PintConverter.hpp"
#include "hx711.h"
// #include "ds18b20.h"

class App
{
public:
  App();
  ~App();
  void run();
  static constexpr int wWidth{640}; //original was 1024 (8bit resized to 512)
  static constexpr int wHeight{480}; //original was 600 (8bit resized to 300)
  static constexpr float xRel{1.25}; // 512/x (adjust for real screen)
  static constexpr float yRel{1.6}; // 300/y (adjust for real screen);
private:
  ValveOperator vo;
  sf::RenderWindow mWindow;
  TextureHolder mTextures;
  sf::Sprite mBackground;
  sf::Sprite mButtonOff;
  sf::Sprite mButtonOn;
  sf::Sprite mXicon;
  sf::Sprite mSecretIconOn;
  sf::Sprite mPintsIcon;
  sf::Sprite mPintDigit_1;
  sf::Sprite mPintDigit_2;
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
  State::ID mState;
  State::ID mOldState;
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
  int mPints;
  // float checkTemp(); //sensor?
  // float mTemp;

  // FPS and TimePerFrame display, will be removed in final version
  void updateStatistics(sf::Time elapsedTime);
  sf::Font mFont;
  sf::Text mStatisticsText;
  sf::Time mStatisticsUpdateTime;
  std::size_t mStatisticsNumFrames;
};

#endif // APP_HPP
