#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

class alien
{
private:
    sf::Image img;
    sf::Texture tex;
    sf::Sprite monster;
    float v;
    sf::Shader moncolor;
    sf::Color MonsterColor;
public:
    float x,y;
    bool life;
    
    sf::Color RandomColor()
    {
        sf::Color color;
        int a=rand()%4+1;
        if(a==1) color=sf::Color::Red;
        if(a==2) color=sf::Color::Magenta;
        if(a==3) color=sf::Color::Green;
        if(a==4) color=sf::Color::Blue;
        return color;
    }
    
    void setup(std::string adress,float a)
    {
        life=true;
        srand(time(0));
        MonsterColor=RandomColor();
        moncolor.loadFromFile(adress+"/alien.frag",sf::Shader::Fragment);
        moncolor.setParameter("tex",sf::Shader::CurrentTexture);
        moncolor.setParameter("color",MonsterColor);
        v=0.5;
        x=a;
        img.loadFromFile(adress+"/alien.png");
        tex.loadFromImage(img);
        monster.setTexture(tex);
        monster.setOrigin(25,18);
        y=0;
    }
    
    bool update(float time)
    {
        bool death=false;
        if((y>=600) && (life) && (y<700)) {life=false;death=true;}
        if(life)y+=v*time;
        return death;
    }
    
    void draw(sf::RenderWindow *window)
    {
        if(life)
        {
            monster.setPosition(x,y);
            window->draw(monster,&moncolor);
        }
    }
};
