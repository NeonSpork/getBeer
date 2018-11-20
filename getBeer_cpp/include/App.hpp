#ifndef APP_HPP
#define APP_HPP

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "StateStack.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>

class App
{
public:
    App();
    ~App(){};
    void run();

private:
    void processInput();
    void update(sf::Time deltaTime);
    void render();
    void updateStatistics(sf::Time deltaTime);
    void registerStates();

private:
    static const sf::Time TimePerFrame;
    sf::RenderWindow mWindow;
    TextureHolder mTextures;
    StateStack mStateStack;

    sf::Time mStatisticsUpdateTime;
    std::size_t mStatisticsNumFrames;
};


#endif // APP_HPP