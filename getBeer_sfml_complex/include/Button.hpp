#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Component.hpp"
#include "ResourceIdentifiers.hpp"
#include "ResourceHolder.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <vector>
#include <string>
#include <memory>
#include <functional>

namespace GUI
{

class Button : public Component
{
public:
  typedef std::shared_ptr<Button> Ptr;
  typedef std::function<void()> Callback;
  Button(const TextureHolder& textures);
  void setCallback(Callback callback);
  virtual void activate();
  virtual void deactivate();
  virtual void handleEvent(const sf::Event& event);
private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  Callback mCallback;
  const sf::Texture& mNormalTexture;
  const sf::Texture& mPressedTexture;
  sf::Sprite mSprite;
};

}

#endif //BUTTON_HPP