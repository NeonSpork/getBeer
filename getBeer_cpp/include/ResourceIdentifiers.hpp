#ifndef RESOURCEIDENTIFIERS_HPP
#define RESOURCEIDENTIFIERS_HPP

namespace sf
{
  class Texture;
}

namespace Textures
{
  enum ID
  {
    // Backgrounds
    default_background,
    tropical_thunder_bg,
    angry_babushka_bg,
    brick_wall,
    // Icons
    angry_babushka_icon,
    beer_button_off,
    beer_button_on,
    beer_button_red_off,
    beer_button_red_on,
    coming_soon_icon,
    cursor,
    default_icon,
    exit,
    ml_icon,
    pints,
    secret_off,
    secret_on,
    temp_icon,
    tropical_thunder_icon,
    // Number images
    num0,
    num1,
    num2,
    num3,
    num4,
    num5,
    num6,
    num7,
    num8,
    num9,
  };
}

// Forward declareation and typedefinition
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

#endif // RESOURCEIDENTIFIERS_HPP