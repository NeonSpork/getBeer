#include "../include/BeerMenuState.hpp"
#include "../include/Button.hpp"
#include "../include/ResourceHolder.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

BeerMenuState::BeerMenuState(StateStack& stack, Context context)
: State(stack, context)
, mGUIContainer()
{
  sf::Texture& texture = context.textures->get(Textures::brick_wall);
  mBackgroundSprite.setTexture(texture);

  // Current button status
  //       default
  // TropT AngryB  soon
  // soon  soon    soon

  // Row 0
  auto defaultButton = std::make_shared<GUI::Button>(*context.textures);
  defaultButton->setPosition(512, 150);
  defaultButton->setCallback([this] ()
  {
    requestStackPop();
    requestStackPush(States::DefaultState);
  });

  // Row 1
  auto tropicalThunder = std::make_shared<GUI::Button>(*context.textures);
  tropicalThunder->setPosition((512-150), (300));
  tropicalThunder->setCallback([this] ()
  {
    requestStackPop();
    requestStackPush(States::TropicalThunder);
  });

  auto angryBabushka = std::make_shared<GUI::Button>(*context.textures);
  angryBabushka->setPosition((512), (300));
  angryBabushka->setCallback([this] ()
  {
    requestStackPop();
    requestStackPush(States::AngryBabushka);
  });

  auto comingSoon0 = std::make_shared<GUI::Button>(*context.textures);
  comingSoon0->setPosition((512+150), (300));
  comingSoon0->setCallback([this] ()
  {
    requestStackPop();
    requestStackPush(States::DefaultState);
  });

  // Row 2
  auto comingSoon1 = std::make_shared<GUI::Button>(*context.textures);
  comingSoon1->setPosition((512-150), (450));
  comingSoon1->setCallback([this] ()
  {
    requestStackPop();
    requestStackPush(States::DefaultState);
  });

  auto comingSoon2 = std::make_shared<GUI::Button>(*context.textures);
  comingSoon2->setPosition((512), (450));
  comingSoon2->setCallback([this] ()
  {
    requestStackPop();
    requestStackPush(States::DefaultState);
  });

  auto comingSoon3 = std::make_shared<GUI::Button>(*context.textures);
  comingSoon3->setPosition((512+150), (450));
  comingSoon3->setCallback([this] ()
  {
    requestStackPop();
    requestStackPush(States::DefaultState);
  });

  mGUIContainer.pack(defaultButton);
  mGUIContainer.pack(tropicalThunder);
  mGUIContainer.pack(angryBabushka);
  mGUIContainer.pack(comingSoon0);
  mGUIContainer.pack(comingSoon1);
  mGUIContainer.pack(comingSoon2);
  mGUIContainer.pack(comingSoon3);
}
