#include <stdio.h>
#include <SFML/Graphics.hpp>

class bullet
{
public:
    sf::RectangleShape bul;
    float x,y;
    float v;
    bool life;
    
    bullet(float a)
    {
        life=true;
        v=-1;
        x=a;
        y=549;
        bul.setSize(sf::Vector2f(3,5));
        bul.setFillColor(sf::Color::White);
        bul.setOrigin(2,0);
        bul.setPosition(x,y);
    }
    
    void update(float time)
    {
        if(y<=0) life=false;
        if(life)
        {
            y+=v*time;
            bul.setPosition(x,y);
        }
    }
    
    void draw(sf::RenderWindow *window,std::string adress,float time)
    {
        sf::Shader shader;
        shader.loadFromFile(adress+"/bullet.frag",sf::Shader::Fragment);
        shader.setParameter("time",time);
        window->draw(bul,&shader);
    }
};
