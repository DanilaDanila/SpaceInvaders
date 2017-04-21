#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "player.cpp"

class game
{
public:
    player ship;
    std::string adr;
    
    void setup(std::string a)
    {
        adr=a;
        ship.setup(adr);
    }
    
    void gameloop(sf::RenderWindow *window,float time)
    {
        window->clear(sf::Color::White);
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) ship.dx=-1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) ship.dx=1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) ship.shoot=true;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) ship.ifboost=true;
        
        ship.update(time);
        
        ship.draw(window);
    }
};
