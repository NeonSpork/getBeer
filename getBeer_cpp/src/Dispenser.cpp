#include <iostream>
#include <SFML/Graphics.hpp>
#include "../include/Dispenser.hpp"

Dispenser::Dispenser()
: mWindow(sf::VideoMode(1024, 600), "getBeer")
, mTexture()
, mBackground()
, mUserKeyboardExit(false)
{
  if (!mTexture.loadFromFile("media/bg/default_background.png"))
  {
    // handle loading error
  }
  mBackground.setTexture(mTexture);
  mBackground.setPosition(0.f, 0.f);
}

void Dispenser::run()
{
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  while (mWindow.isOpen())
  {
    processEvents();
    timeSinceLastUpdate += clock.restart();
    while (timeSinceLastUpdate > TimePerFrame)
    {
      timeSinceLastUpdate -= TimePerFrame;
      processEvents();
      update(TimePerFrame);
    }
    render();
  }
}

void Dispenser::processEvents()
{
  sf::Event event;
  while (mWindow.pollEvent(event))
  {
    switch (event.type)
    {
      case sf::Event::KeyPressed:
        handleKeyboardInput(event.key.code, true);
        break;
      case sf::Event::KeyReleased:
        handleKeyboardInput(event.key.code, false);
        break;
      case sf::Event::Closed:
        mWindow.close();
        break;
      case sf::Event::MouseButtonPressed:
        // handleMouseInput(event.mouse.button, true);
        break;
      case sf::Event::MouseButtonReleased:
      //   handle mouse stuff
        break;
    }
  }
}

void Dispenser::handleKeyboardInput(sf::Keyboard::Key key, bool isPressed)
{
  if (key == sf::Keyboard::Escape)
  {
    mUserKeyboardExit = isPressed;
  }
}

void Dispenser::handleMouseInput(sf::Mouse::Button button, bool isPressed)
{
  if (button == sf::Mouse::Left)
  {
    //do things correctly
  }
}

void Dispenser::update(sf::Time deltaTime)
{
  if (mUserKeyboardExit)
  {
    mWindow.close();
  }
}

void Dispenser::render()
{
  mWindow.clear();
  mWindow.draw(mBackground);
  mWindow.display();
}