#ifndef DISPENSER_HPP
#define DISPENSER_HPP

#include <SFML/Graphics.hpp>

class Dispenser
{
public:
    Dispenser();
    ~Dispenser(){};
    void run();
private:
    void processEvents();
    void handleKeyboardInput(sf::Keyboard::Key key, bool isPressed);
    void handleMouseInput(sf::Mouse::Button button, bool isPressed);
    void update(sf::Time deltaTime);
    void render();

private:
    sf::RenderWindow mWindow;
    sf::Texture mTexture;
    sf::Sprite mBackground;
    bool mUserKeyboardExit;
    const sf::Time TimePerFrame = sf::seconds(1.f/60.f);
};

#endif