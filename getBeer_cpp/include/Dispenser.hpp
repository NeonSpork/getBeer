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
    void update();
    void render();

private:
    sf::RenderWindow mWindow;
};

#endif