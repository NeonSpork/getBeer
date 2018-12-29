#include "../include/App.hpp"

App::App()
: mWindow(sf::VideoMode(wWidth, wHeight), "getBeer")
, mBackground()
, mButtonOff()
, mButtonOn()
, mXicon()
, mSecretIconOn()
, mIcon0()
, mIcon1()
, mIcon2()
, mIcon3()
, mIcon4()
, mIcon5()
, mIcon6()
, mIcon7()
, mIcon8()
, mIcon9()
, mIcon10()
, mIcon11()
, mIcon12()
, mState()
, TimePerFrame(sf::seconds(1.f/60.f))
{
  setState(State::ID::Default);
  ValveOperator vo;
  vo.openValve(Valve::beer, false);
  vo.status('b', false);
  vo.openValve(Valve::secret, false);
  vo.status('s', false);
  loadTextures();
  mBackground.setTexture(mTextures.get(Textures::default_background));
  mBackground.setPosition(0.f, 0.f);
  mButtonOff.setTexture(mTextures.get(Textures::beer_button_off));
  mButtonOff.setPosition((wWidth-200), (wHeight-200));
  mButtonOn.setTexture(mTextures.get(Textures::beer_button_on));
  mButtonOn.setPosition((wWidth-200), (wHeight-200));
  mXicon.setTexture(mTextures.get(Textures::exit));
  mXicon.setPosition(0.f, 0.f);
  mSecretIconOn.setTexture(mTextures.get(Textures::secret_on));
  mSecretIconOn.setPosition(525, 75);
  mIcon0.setTexture(mTextures.get(Textures::default_icon));
  mIcon1.setTexture(mTextures.get(Textures::tropical_thunder_icon));
  mIcon2.setTexture(mTextures.get(Textures::angry_babushka_icon));
  mIcon3.setTexture(mTextures.get(Textures::coming_soon_icon));
  mIcon4.setTexture(mTextures.get(Textures::coming_soon_icon));
  mIcon5.setTexture(mTextures.get(Textures::coming_soon_icon));
  mIcon6.setTexture(mTextures.get(Textures::coming_soon_icon));
  mIcon7.setTexture(mTextures.get(Textures::coming_soon_icon));
  mIcon8.setTexture(mTextures.get(Textures::coming_soon_icon));
  mIcon9.setTexture(mTextures.get(Textures::coming_soon_icon));
  mIcon10.setTexture(mTextures.get(Textures::coming_soon_icon));
  mIcon11.setTexture(mTextures.get(Textures::coming_soon_icon));
  mIcon12.setTexture(mTextures.get(Textures::coming_soon_icon));
  mIcon0.setPosition(((wWidth/2)-150), 0);
  mIcon1.setPosition(((wWidth/2)-300), 150);
  mIcon2.setPosition(((wWidth/2)-150), 150);
  mIcon3.setPosition(((wWidth/2)), 150);
  mIcon4.setPosition(((wWidth/2)+150), 150);
  mIcon5.setPosition(((wWidth/2)-300), 300);
  mIcon6.setPosition(((wWidth/2)-150), 300);
  mIcon7.setPosition(((wWidth/2)), 300);
  mIcon8.setPosition(((wWidth/2)+150), 300);
  mIcon9.setPosition(((wWidth/2)-300), 450);
  mIcon10.setPosition(((wWidth/2)-150), 450);
  mIcon11.setPosition(((wWidth/2)), 450);
  mIcon12.setPosition(((wWidth/2)+150), 450);
}

void App::run()
{
  // sf::Clock clock;
  // sf::Time timeSinceLastUpdate = sf::Time::Zero;
  while (mWindow.isOpen())
  {
    events();
    uodate();
    // timeSinceLastUpdate += clock.restart();
    // while (timeSinceLastUpdate > TimePerFrame)
    // {
    //   timeSinceLastUpdate -= TimePerFrame;
    //   events();
    //   update(TimePerFrame);
    // }
    render();
    std::cout << "Frame.\n";
  }
}

void App::events()
{
  sf::Event event;
  while (mWindow.pollEvent(event))
  {
    // sf::Vector2i origMousePos = sf::Mouse::getPosition(mWindow);
    sf::Vector2i origTouchPos = sf::Touch::getPosition(0, mWindow);
    switch (event.type)
    {
      case sf::Event::Closed:
        mWindow.close();
        break;
      case sf::Event::KeyPressed:
        handleInput(event.key.code, true);
        break;
      case sf::Event::KeyReleased:
        handleInput(event.key.code, false);
        break;
      case sf::Event::MouseButtonPressed:
        handleInput(event.mouseButton.button, true);
        break;
      // case sf::Event::MouseMoved:
      //   if (event.mouseButton.button == sf::Mouse::Left)
      //     swipe(origMousePos.x, event.mouseMove.x);
      //   break;
      case sf::Event::MouseButtonReleased:
        handleInput(event.mouseButton.button, false);
        vo.openValve(Valve::beer, false);
        vo.status('b', false);
        vo.openValve(Valve::secret, false);
        vo.status('s', false);
        break;
      case sf::Event::TouchBegan:
        handleInput(event.touch.finger, true);
        break;
      case sf::Event::TouchEnded:
        handleInput(event.touch.finger, false);
        vo.openValve(Valve::beer, false);
        vo.status('b', false);
        vo.openValve(Valve::secret, false);
        vo.status('s', false);
        break;
      case sf::Event::TouchMoved:
        swipe(origTouchPos.x, event.touch.x);
        break;
    }
  }
}

void App::update(const sf::Time& TimePerFrame)
{
  if (mState == State::ID::AngryBabushka)
  {
    mButtonOff.setTexture(mTextures.get(Textures::beer_button_red_off));
    mButtonOn.setTexture(mTextures.get(Textures::beer_button_red_on));
  }
  else
  {
    mButtonOff.setTexture(mTextures.get(Textures::beer_button_off));
    mButtonOn.setTexture(mTextures.get(Textures::beer_button_on));
  }
  switch (mState)
  {
    case State::ID::None: case State::ID::Default:
      mBackground.setTexture(mTextures.get(Textures::default_background));
      break;
    case State::ID::TropicalThunder:
      mBackground.setTexture(mTextures.get(Textures::tropical_thunder_bg));
      break;
    case State::ID::AngryBabushka:
      mBackground.setTexture(mTextures.get(Textures::angry_babushka_bg));
      break;
    case State::ID::BeerMenu:
      mBackground.setTexture(mTextures.get(Textures::brick_wall));
      break;
    default:
      mBackground.setTexture(mTextures.get(Textures::default_background));
      break;
  }
}

void App::render()
{
  mWindow.clear();
  mWindow.draw(mBackground);
  if (mState != State::ID::BeerMenu)
  {
    mWindow.draw(mXicon);
    if (vo.getBeerStatus())
    {
      mWindow.draw(mButtonOn);
    }
    if (!vo.getBeerStatus())
    {
      mWindow.draw(mButtonOff);
    }
    if (vo.getSecretStatus())
    {
      mWindow.draw(mSecretIconOn);
    }
  }
  if (mState == State::ID::BeerMenu)
  {
    mWindow.draw(mIcon0);
    mWindow.draw(mIcon1);
    mWindow.draw(mIcon2);
    mWindow.draw(mIcon3);
    mWindow.draw(mIcon4);
    mWindow.draw(mIcon5);
    mWindow.draw(mIcon6);
    mWindow.draw(mIcon7);
    mWindow.draw(mIcon8);
    mWindow.draw(mIcon9);
    mWindow.draw(mIcon10);
    mWindow.draw(mIcon11);
    mWindow.draw(mIcon12);
  }
  mWindow.display();
}

void App::handleInput(sf::Keyboard::Key key, bool isPressed)
{
  if (key == sf::Keyboard::Escape)
    mWindow.close();
}

void App::handleInput(sf::Mouse::Button button, bool isPressed)
{
  sf::Vector2i pos = sf::Mouse::getPosition(mWindow);
  if (button ==  sf::Mouse::Left)
  {
    if (pos.x > (wWidth-100) && pos.y < 100)
    {
      mWindow.close();
    }
    if (mState != State::ID::BeerMenu)
    {
      if (pos.x < 100 && pos.y < 100)
        mState = State::ID::BeerMenu;
      if ((pos.x > (wWidth-200)) && (pos.y > (wHeight-200)))
      {
        vo.openValve(Valve::beer, isPressed);
        vo.status('b', isPressed);
        if (isPressed)
        {
          std::cout << "Button pressed!\n";
        }
        if (!isPressed)
        {
          std::cout << "Button released!\n";
        }
      }
      // THIS ONE IS ONLY FOR TESTING. DOUBLE TOUCH WILL BE IN THE LIVE VERSION
      if (mState == State::ID::Default)
      {
        if (((pos.x > 575) && (pos.x < 825)) && ((pos.y > 25) && (pos.y < 125)))
        {
          vo.openValve(Valve::secret, isPressed);
          vo.status('s', isPressed);
          if (isPressed)
          {
            std::cout << "Secret pressed!!\n";
          }
          if (!isPressed)
          {
            std::cout << "Secret released!!\n";
          }
        }
      }
    }
    if (mState == State::ID::BeerMenu)
    {
      /* BUTTON GRID
                00
            1  2  3  4
            5  6  7  8
            9 10 11 12
      */
      // To be updated with graphics as more beers get added to repetoire
      int xx = wWidth/2;
      if ((pos.x > xx-150 && pos.x < xx+150) && (pos.y < 150))
      // 00
      {
        mState = State::ID::Default;
      }
      if ((pos.x > xx-300 && pos.x < xx-150) && (pos.y > 150 && pos.y < 300))
      // 1
      {
        mState = State::ID::TropicalThunder;
      }
      if ((pos.x > xx-150 && pos.x < xx) && (pos.y > 150 && pos.y < 300))
      // 2
      {
        mState = State::ID::AngryBabushka;
      }
      if ((pos.x > xx && pos.x < xx+150) && (pos.y > 150 && pos.y < 300))
      // 3
      {
        mState = State::ID::Default;
      }
      if ((pos.x > xx+150 && pos.x < xx+300) && (pos.y > 150 && pos.y < 300))
      // 4
      {
        mState = State::ID::Default;
      }
      if ((pos.x > xx-300 && pos.x < xx-150) && (pos.y > 300 && pos.y < 450))
      // 5
      {
        mState = State::ID::Default;
      }
      if ((pos.x > xx-150 && pos.x < xx) && (pos.y > 300 && pos.y < 450))
      // 6
      {
        mState = State::ID::Default;
      }
      if ((pos.x > xx && pos.x < xx+150) && (pos.y > 300 && pos.y < 450))
      // 7
      {
        mState = State::ID::Default;
      }
      if ((pos.x > xx+150 && pos.x < xx+300) && (pos.y > 300 && pos.y < 450))
      // 8
      {
        mState = State::ID::Default;
      }
      if ((pos.x > xx-300 && pos.x < xx-150) && (pos.y > 450 && pos.y < 600))
      // 9
      {
        mState = State::ID::Default;
      }
      if ((pos.x > xx-150 && pos.x < xx) && (pos.y > 450 && pos.y < 600))
      // 10
      {
        mState = State::ID::Default;
      }
      if ((pos.x > xx && pos.x < xx+150) && (pos.y > 450 && pos.y < 600))
      // 11
      {
        mState = State::ID::Default;
      }
      if ((pos.x > xx+150 && pos.x < xx+300) && (pos.y > 450 && pos.y < 600))
      // 12
      {
        mState = State::ID::Default;
      }
    }
  }
}

void App::handleInput(unsigned int touch, bool isPressed)
// TODO update this when get hands on touch screen
{
  sf::Vector2i pos0 = sf::Touch::getPosition(0, mWindow);
  if (pos0.x > (wWidth-100) && pos0.y < 100)
      mWindow.close();
  if (pos0.x > (wHeight-200) && pos0.y > (wWidth-200))
  {
    vo.openValve(Valve::beer, isPressed);
    vo.status('b', isPressed);
    std::cout << "Button pressed!\n";
  }
  if ((pos0.x > 575 && pos0.x < 825) && (pos0.y > 25 && pos0.y < 125))
  {
    sf::Vector2i pos1 = sf::Touch::getPosition(1, mWindow);
    if ((pos1.x > 250 && pos1.x < 500) && (pos1.y > 100 && pos1.y < 200))
    {
      vo.openValve(Valve::secret, isPressed);
      vo.status('s', isPressed);
      std::cout << "Secret pressed!!\n";
    }
  }
}

void App::swipe(int oldX, int newX)
{
  if (oldX < newX)
    setState(State::ID::BeerMenu);
  if ((oldX > newX) && (mState == State::ID::BeerMenu))
    setState(State::ID::Default);
}

void App::setState(State::ID name)
{
  mState = name;
}

void App::loadTextures()
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
