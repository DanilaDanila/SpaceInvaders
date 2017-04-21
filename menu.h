//
//  men.h
//  cater
//
//  Created by Danila Manakov on 09.04.17.
//  Copyright © 2017 Danila Manacov. All rights reserved.
//

#ifndef menu_h
#define menu_h

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class button
{
public:
    sf::Sound tick;
    sf::IntRect coords;
    sf::Sprite b;
    sf::Texture tex;
    sf::Color onit;
    sf::Color defcolor;
    bool click;
    bool play;
    
    button(sf::Sprite t,sf::Sound bu,sf::IntRect cor,sf::Color c,sf::Color d)
    {
        tick=bu;
        tick.setVolume(100);
        play=false;
        click=false;
        coords=cor;
        defcolor=d;
        onit=c;
        b=t;
        b.setPosition(coords.left,coords.top);
        tick.setLoop(false);
    }
    
    void update(sf::RenderWindow *window,sf::IntRect pos,bool cl)
    {
        if(pos.intersects(coords)) {b.setColor(onit);if(cl) click=true;if(!play) {tick.play();play=true;}}
        
        if(!pos.intersects(coords)) {b.setColor(defcolor);play=false;tick.setPlayingOffset(sf::seconds(0));tick.stop();}
        
        window->draw(b);
    }
};

class menu
{
public:
    std::vector<button> buttons;
    sf::Sound defaltsound;
    sf::Music fonmusic;
    sf::RectangleShape fon;
    sf::Shader fonshader;
    
    void setup(sf::Sound buf,std::string adress,float volume,std::string adr)
    {
        fon.setSize(sf::Vector2f(800,600));
        fon.setFillColor(sf::Color::White);
        fonshader.loadFromFile(adr+"/fon.frag",sf::Shader::Fragment);
        defaltsound=buf;
        fonmusic.openFromFile(adress);
        fonmusic.setVolume(volume);
        //fonmusic.play();
    }
    
    void reboot()
    {
        //fonmusic.play();
        for(int i=0;i<buttons.size();i++) buttons[i].click=false;
    }
    
    void createbutton(sf::Sprite sprite,sf::IntRect cords,sf::Color defalt,sf::Color onbutton)
    {
        buttons.push_back(button(sprite,defaltsound,cords,onbutton,defalt));
    }
    
    void draw(sf::RenderWindow *window,sf::Vector2f pos,bool click,float time)
    {
        fonshader.setParameter("time",time);
        window->draw(fon,&fonshader);
        for(int i=0;i<buttons.size();i++)
        {
            buttons[i].update(window,sf::IntRect(pos.x,pos.y,1,1),click);
            if(buttons[i].click) {fonmusic.stop();break;}
        }
    }
    
    ~menu()
    {
        fonmusic.stop();
        for(int i=0;i<buttons.size();i++) buttons[i].tick.stop();
    }
};

#endif /* men_h */
