#include "../include/App.hpp"

App::App()
: mWindow(sf::VideoMode(wWidth, wHeight), "getBeer", sf::Style::Fullscreen)
, mBackground()
, mButtonOff()
, mButtonOn()
, mXicon()
, mSecretIconOn()
, mPintsIcon()
, mPintDigit_1()
, mPintDigit_2()
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
, mPints(0)
, mTemp(0)
, mState()
, mOldState()
, mNewButtonState(false)
, mOldButtonState(false)
, mNewSecretState(false)
, mOldSecretState(false)
, mRenderScreen(true)
, TimePerFrame(sf::seconds(1.f/60.f))
, TimePerSensorUpdate(sf::seconds(1.f))
// FPS and TimePerFrame display, will be removed in final version
, mFont()
, mStatisticsText()
, mStatisticsUpdateTime()
, mStatisticsNumFrames(0)
{
  mWindow.setMouseCursorVisible(false);
  // mWindow.setFramerateLimit(15);
  setState(State::ID::Default);
  mOldState = mState;
  mOldPints = mPints;
  ValveOperator vo;
  Sensor sensor;
  vo.openValve('b', false);
  vo.openValve('s', false);
  loadTextures();
  placeTextures();

  PLUGIN_NAME = "PyTemp";
  pluginModule = PyImport_Import(PyString_FromString(PLUGIN_NAME));
  getTemp = PyObject_GetAttrString(pluginModule, "getTemp");
  args = Py_BuildValue("(s)");

  // FPS and TimePerFrame display, will be removed in final version
  mFont.loadFromFile("media/Sansation.ttf");
  mStatisticsText.setFont(mFont);
  mStatisticsText.setPosition(50.f, 5.f);
  mStatisticsText.setCharacterSize(10);
}

App::~App()
{
  digitalWrite(5, false);
  digitalWrite(6, false);
}

void App::run()
{
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  sf::Time timeSinceSensorUpdate = sf::Time::Zero;
  while (mWindow.isOpen())
  {
    events();
    sf::Time elapsedTime = clock.restart();
    timeSinceLastUpdate += elapsedTime;
    timeSinceSensorUpdate += elapsedTime;
    while (timeSinceLastUpdate > TimePerFrame)
    {
      timeSinceLastUpdate -= TimePerFrame;
      events();
      update(TimePerFrame);
      if (timeSinceSensorUpdate > TimePerSensorUpdate)
      {
        mPints = checkPints();
        mTemp = checkTemp();
        timeSinceSensorUpdate = sf::seconds(0.f);
      }
      stateCheck();
    }
    updateStatistics(elapsedTime);
    if (mRenderScreen)
    {
      render();
      mRenderScreen = false;
    }
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
        vo.openValve('b', false);
        vo.openValve('s', false);
        break;
      case sf::Event::TouchBegan:
        std::cout << "Touch began.\n";      
        handleInput(event.touch.finger, true);
        break;
      case sf::Event::TouchEnded:
        std::cout << "Touch ended.\n";      
        handleInput(event.touch.finger, false);
        vo.openValve('b', false);
        vo.openValve('s', false);
        break;
      case sf::Event::TouchMoved:
        std::cout << "Touch moved.\n";      
        swipe(origTouchPos.x, event.touch.x);
        break;
    }
  }
}

void App::update(const sf::Time& TimePerFrame)
{
  if (mOldState != mState)
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
    mOldState = mState;
    mRenderScreen = true;
  }
  if (mOldPints != mPints)
  {
    if (mPints < 10)
    {
      mPintDigit_1.setTexture(mTextures.get(Textures::ID(mPints)));
    }
    if (mPints >= 10 && mPints < 100)
    {
      int first = ((mPints/10)%10);
      int second = (mPints%10);
      mPintDigit_1.setTexture(mTextures.get(Textures::ID(first)));
      mPintDigit_2.setTexture(mTextures.get(Textures::ID(second)));
    }
    if (mPints >= 100)
    {
      mPintDigit_1.setTexture(mTextures.get(Textures::num9));
      mPintDigit_2.setTexture(mTextures.get(Textures::num9));
    }
    mOldPints = mPints;
    mRenderScreen = true;
  }
  mNewButtonState = vo.getBeerStatus();
  mNewSecretState = vo.getSecretStatus();
}

void App::stateCheck()
{
  if (mNewButtonState != mOldButtonState)
  {
    mRenderScreen = true;
    mOldButtonState = mNewButtonState;
  }
  if (mNewSecretState != mOldSecretState)
  {
    mRenderScreen = true;
    mOldSecretState = mNewSecretState;
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
    mWindow.draw(mPintsIcon);
    if (mPints < 10)
    {
      mWindow.draw(mPintDigit_1);
    }
    if (mPints >= 10)
    {
      mWindow.draw(mPintDigit_1);
      mWindow.draw(mPintDigit_2);
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
  mWindow.draw(mStatisticsText);
  mWindow.display();
  mRenderScreen = false;
}

int App::checkPints()
{
  int ml = sensor.checkWeight();
  int pints = ml/500;
  return pints;
}

int App::checkTemp()
{
  float temp = callPython();
  float roundedTemp = std::round(temp);
  int intTemp = static_cast<int>(roundedTemp);
  std::cout << "intTemp: " << intTemp << std::endl;
  return intTemp;
}

float App::callPython()
{
  // PyObject* pluginModule = PyImport_Import(PyString_FromString(PLUGIN_NAME));
  // PyObject* getTemp = PyObject_GetAttrString(pluginModule, "getTemp");
  // PyObject* args = Py_BuildValue("(s)");
  PyObject* result = PyObject_CallObject(getTemp, args);
  return PyFloat_AsDouble(result);
}

void App::updateStatistics(sf::Time elapsedTime)
{
  mStatisticsUpdateTime += elapsedTime;
  mStatisticsNumFrames += 1;
  if (mStatisticsUpdateTime >= sf::seconds(1.0f))
  {
    mStatisticsText.setString(
      "FPS: " + std::to_string(mStatisticsNumFrames) + "\n" +
      "TimePerFrame: " + std::to_string(mStatisticsUpdateTime.asMicroseconds()/mStatisticsNumFrames) + " microsec");
    mStatisticsUpdateTime -= sf::seconds(1.0f);
    mStatisticsNumFrames = 0;
  }
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
    if (pos.x > (wWidth-(100*xRel)) && pos.y < (100*yRel))
    {
      mWindow.close();
    }
    if (mState != State::ID::BeerMenu)
    {
      if (pos.x < (100*xRel) && pos.y < (100*yRel))
        mState = State::ID::BeerMenu;
      if ((pos.x > (wWidth-(200*xRel))) && (pos.y > (wHeight-(200*yRel))))
      {
        vo.openValve('b', isPressed);
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
        if (((pos.x > (575*xRel)) && (pos.x < (825*xRel))) && ((pos.y > (25*yRel)) && (pos.y < (125*yRel))))
        {
          vo.openValve('s', isPressed);
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
        +--+--+--+--+
        |  |00000|  |
        +--+--+--+--+
        |01|02|03|04|
        +--+--+--+--+
        |05|06|07|08|
        +--+--+--+--+
        |09|10|11|12|
        +--+--+--+--+
      */
      // To be updated with graphics as more beers get added to repetoire
      int xx = (wWidth)/2;
      if ((pos.x > (xx-(150*xRel)) && pos.x < (xx+(150*xRel))) && (pos.y < (150)*yRel))
      // 00
      {
        mState = State::ID::Default;
      }
      if ((pos.x > (xx-(300*xRel)) && pos.x < (xx-(150*xRel))) && (pos.y > (150*yRel) && pos.y < (300*yRel)))
      // 1
      {
        mState = State::ID::TropicalThunder;
      }
      if ((pos.x > (xx-(150*xRel)) && pos.x < xx) && (pos.y > (150*yRel) && pos.y < (300*yRel)))
      // 2
      {
        mState = State::ID::AngryBabushka;
      }
      if ((pos.x > xx && pos.x < (xx+(150*xRel))) && (pos.y > (150*yRel) && pos.y < (300*yRel)))
      // 3
      {
        mState = State::ID::Default;
      }
      if ((pos.x > (xx+(150*xRel)) && pos.x < (xx+(300*xRel))) && (pos.y > (150*yRel) && pos.y < (300*yRel)))
      // 4
      {
        mState = State::ID::Default;
      }
      if ((pos.x > (xx-(300*xRel)) && pos.x < (xx-(150*xRel))) && (pos.y > (300*yRel) && pos.y < (450*yRel)))
      // 5
      {
        mState = State::ID::Default;
      }
      if ((pos.x > (xx-(150*xRel)) && pos.x < xx) && (pos.y > (300*yRel) && pos.y < (450*yRel)))
      // 6
      {
        mState = State::ID::Default;
      }
      if ((pos.x > xx && pos.x < (xx+(150*xRel))) && (pos.y > (300*yRel) && pos.y < (450*yRel)))
      // 7
      {
        mState = State::ID::Default;
      }
      if ((pos.x > (xx+(150*xRel)) && pos.x < (xx+(300*xRel))) && (pos.y > (300*yRel) && pos.y < (450*yRel)))
      // 8
      {
        mState = State::ID::Default;
      }
      if ((pos.x > (xx-(300*xRel)) && pos.x < (xx-(150*xRel))) && (pos.y > (450*yRel) && pos.y < (600*yRel)))
      // 9
      {
        mState = State::ID::Default;
      }
      if ((pos.x > (xx-(150*xRel)) && pos.x < xx) && (pos.y > (450*yRel) && pos.y < (600*yRel)))
      // 10
      {
        mState = State::ID::Default;
      }
      if ((pos.x > xx && pos.x < (xx+(150*xRel))) && (pos.y > (450*yRel) && pos.y < (600*yRel)))
      // 11
      {
        mState = State::ID::Default;
      }
      if ((pos.x > (xx+(150*xRel)) && pos.x < (xx+(300*xRel))) && (pos.y > (450*yRel) && pos.y < (600*yRel)))
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
  if (pos0.x > (wWidth-(100*xRel)) && pos0.y < (100*yRel))
      mWindow.close();
  if (pos0.x > (wWidth-(200*xRel)) && pos0.y > (wHeight-(200*yRel)))
  {
    vo.openValve('b', isPressed);
    std::cout << "Button pressed!\n";
  }
  if ((pos0.x > (575*xRel) && pos0.x < (825*xRel)) && (pos0.y > (25*yRel) && pos0.y < (125*yRel)))
  {
    sf::Vector2i pos1 = sf::Touch::getPosition(1, mWindow);
    if ((pos1.x > (250*xRel) && pos1.x < (500*xRel)) && (pos1.y > (100*yRel) && pos1.y < (200*yRel)))
    {
      vo.openValve('s', isPressed);
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

void App::placeTextures()
{
  mBackground.setTexture(mTextures.get(Textures::default_background));
  mBackground.scale(xRel, yRel);
  mBackground.setPosition(0.f, 0.f);
  mButtonOff.setTexture(mTextures.get(Textures::beer_button_off));
  mButtonOff.scale(xRel, yRel);
  mButtonOff.setPosition((wWidth-(200*xRel)), (wHeight-(200*yRel)));
  mButtonOn.setTexture(mTextures.get(Textures::beer_button_on));
  mButtonOn.scale(xRel, yRel);
  mButtonOn.setPosition((wWidth-(200*xRel)), (wHeight-(200*yRel)));
  mXicon.setTexture(mTextures.get(Textures::exit));
  mXicon.scale(xRel, yRel);
  mXicon.setPosition(0.f, 0.f);
  mSecretIconOn.setTexture(mTextures.get(Textures::secret_on));
  mSecretIconOn.scale(xRel, yRel);
  mSecretIconOn.setPosition((525*xRel), (75*yRel));
  mPintsIcon.setTexture(mTextures.get(Textures::pints));
  mPintsIcon.scale(xRel, xRel);
  mPintsIcon.setPosition(0.f, (wHeight-(100*yRel)));
  mPintDigit_1.setTexture(mTextures.get(Textures::num0));
  mPintDigit_1.scale(xRel, yRel);
  mPintDigit_1.setPosition(180*xRel, (wHeight-(100*yRel)));
  mPintDigit_2.setTexture(mTextures.get(Textures::num0));
  mPintDigit_2.scale(xRel, yRel);
  mPintDigit_2.setPosition(230*xRel, (wHeight-(100*yRel)));
  mIcon0.setTexture(mTextures.get(Textures::default_icon));
  mIcon0.scale(xRel, yRel);
  mIcon1.setTexture(mTextures.get(Textures::tropical_thunder_icon));
  mIcon1.scale(xRel, yRel);
  mIcon2.setTexture(mTextures.get(Textures::angry_babushka_icon));
  mIcon2.scale(xRel, yRel);
  mIcon3.setTexture(mTextures.get(Textures::coming_soon_icon));
  mIcon3.scale(xRel, yRel);
  mIcon4.setTexture(mTextures.get(Textures::coming_soon_icon));
  mIcon4.scale(xRel, yRel);
  mIcon5.setTexture(mTextures.get(Textures::coming_soon_icon));
  mIcon5.scale(xRel, yRel);
  mIcon6.setTexture(mTextures.get(Textures::coming_soon_icon));
  mIcon6.scale(xRel, yRel);
  mIcon7.setTexture(mTextures.get(Textures::coming_soon_icon));
  mIcon7.scale(xRel, yRel);
  mIcon8.setTexture(mTextures.get(Textures::coming_soon_icon));
  mIcon8.scale(xRel, yRel);
  mIcon9.setTexture(mTextures.get(Textures::coming_soon_icon));
  mIcon9.scale(xRel, yRel);
  mIcon10.setTexture(mTextures.get(Textures::coming_soon_icon));
  mIcon10.scale(xRel, yRel);
  mIcon11.setTexture(mTextures.get(Textures::coming_soon_icon));
  mIcon11.scale(xRel, yRel);
  mIcon12.setTexture(mTextures.get(Textures::coming_soon_icon));
  mIcon12.scale(xRel, yRel);
  mIcon0.setPosition(((wWidth/2)-(150*xRel)), 0);
  mIcon1.setPosition(((wWidth/2)-(300*xRel)), (150*yRel));
  mIcon2.setPosition(((wWidth/2)-(150*xRel)), (150*yRel));
  mIcon3.setPosition((wWidth/2), (150*yRel));
  mIcon4.setPosition(((wWidth/2)+(150*xRel)), (150*yRel));
  mIcon5.setPosition(((wWidth/2)-(300*xRel)), (300*yRel));
  mIcon6.setPosition(((wWidth/2)-(150*xRel)), (300*yRel));
  mIcon7.setPosition(((wWidth/2)), (300*yRel));
  mIcon8.setPosition(((wWidth/2)+(150*xRel)), (300*yRel));
  mIcon9.setPosition(((wWidth/2)-(300*xRel)), (450*yRel));
  mIcon10.setPosition(((wWidth/2)-(150*xRel)), (450*yRel));
  mIcon11.setPosition(((wWidth/2)), (450*yRel));
  mIcon12.setPosition(((wWidth/2)+(150*xRel)), (450*yRel));
}