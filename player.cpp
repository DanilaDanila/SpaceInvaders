#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "bullet.cpp"
#include "aliens.cpp"
#include <iostream>

class player//50x41
{
private:
    sf::SoundBuffer shootmusic;
    sf::Sound shootsound;
    sf::SoundBuffer alienbuffer;
    sf::Sound aliensound;
    sf::Texture tex;
    sf::Sprite ship;
    sf::RectangleShape boost;
    int bleft;
    float boostadder;
    sf::RectangleShape overheat;
    int overnumber;
    float heatadder;
    bool canshoot;
    sf::Shader BoostShader;
    std::vector<bullet> bullets;
    alien aliens[15];
    int allalians=15;
    sf::Clock alientimer;
    sf::Clock clock;
    float newalien;
    float delay;
    std::string adr;
    sf::Clock SinClock;
    sf::Font font;
    sf::Text score;
    int count=0;
    float x;
    sf::SoundBuffer buffer;
    sf::Sound death;
public:
    float dx;
    int lives=5;
    bool shoot;
    bool ifboost;
    
    int spawn()
    {
        int a=rand()%740+40;
        return a;
    }
    
    void setup(std::string adress)
    {
        lives=5;
        heatadder=0;
        boostadder=0;
        overnumber=0;
        canshoot=true;
        bleft=150;
        boost.setSize(sf::Vector2f(bleft,20));
        boost.setFillColor(sf::Color::Red);
        boost.setPosition(20,570);
        font.loadFromFile(adress+"/Arial.ttf");
        score.setFont(font);
        score.setCharacterSize(20);
        score.setStyle(sf::Text::Bold);
        score.setColor(sf::Color::White);
        adr=adress;
        newalien=1000000;
        delay=200000;
        shoot=false;
        tex.loadFromFile(adress+"/spaceship.png");
        tex.setSmooth(true);
        ship.setTexture(tex);
        ship.setTextureRect(sf::IntRect(0,41,50,-41));
        ship.setOrigin(25,21);
        x=400;
        BoostShader.loadFromFile(adress+"/boost.frag",sf::Shader::Fragment);
        ship.setPosition(x,570);
        shootmusic.loadFromFile(adr+"/shoot.wav");
        shootsound.setBuffer(shootmusic);
        shootsound.setVolume(20);
        overheat.setSize(sf::Vector2f(overnumber,20));
        overheat.setFillColor(sf::Color::Red);
        overheat.setPosition(780,570);
        alienbuffer.loadFromFile(adr+"/alien.wav");
        aliensound.setBuffer(alienbuffer);
        buffer.loadFromFile(adress+"/alienkill.wav");
        death.setBuffer(buffer);
        for(int i=0;i<15;i++) aliens[i].life=false;
    }
    
    void update(float time)
    {
        if(time!=0)
        {
            if((ifboost) && (bleft>0)) dx*=2;
            if((shoot) && (clock.getElapsedTime().asMicroseconds()>delay) && (canshoot))
            {
                shootsound.play();
                bullets.push_back(bullet(x));
                clock.restart();
            }
            //////////////
            if(alientimer.getElapsedTime().asMicroseconds()>=newalien)
            {
                for(int i=0;i<allalians;i++) if(aliens[i].life==false){aliens[i].setup(adr,spawn());break;}
                alientimer.restart();
            }
            for(int i=0;i<allalians;i++)
            {
                bool d=aliens[i].update(time);
                if(d)
                {
                    lives--;
                    aliensound.play();
                }
            }
            //////////////
            if((x+dx*time<775) && (x+dx*time>25))x+=dx*time;
            ship.setPosition(x,560);
            dx=0;
            for(int i=0;i<bullets.size();i++)
            {
                if(!bullets[i].life) bullets.erase(bullets.begin()+i);
                bullets[i].update(time);
            }
            
            for(int i=0;i<15;i++)
            {
                float posx=aliens[i].x;
                float posy=aliens[i].y;
                for(int j=0;j<bullets.size();j++)
                {
                    float x=bullets[j].x;
                    float y=bullets[j].y;
                    if((x>posx-25) && (x<posx+25) && (y>posy-18) && (y<posy+18) && aliens[i].life)
                    {
                        bullets[j].life=false;
                        aliens[i].life=false;
                        count+=100;
                        death.play();
                        if(count==5000) {count=0;lives++;}
                    }
                }
            }
            BoostShader.setParameter("time",time);
            if(bleft>150) bleft=150;
            if(bleft<0) bleft=0;
            if((!ifboost) && (bleft<=150))
            {
                if(int(boostadder)==1)
                {
                    bleft+=1;
                    boostadder=0;
                }
                boostadder+=0.05*time;
            }
            else {boostadder=0;if(bleft>0){bleft-=2;}}
            ifboost=false;
            
            if(shoot && canshoot)
            {
                overnumber++;
                if(overnumber>=150)
                {
                    canshoot=false;
                    overnumber=150;
                }
            }
            else
                if(overnumber>0)
                {
                    heatadder-=0.1*time;
                    if(int(heatadder)<=-1) {overnumber--;heatadder=0;}
                }
            if(overnumber<=0) {overnumber=0;canshoot=true;}
            
            overheat.setPosition(780-overnumber,570);
            overheat.setSize(sf::Vector2f(overnumber,20));
            boost.setSize(sf::Vector2f(bleft,20));
            shoot=false;
        }
    }
    
    void draw(sf::RenderWindow *window)
    {
        window->clear(sf::Color::Black);
        if(SinClock.getElapsedTime().asMicroseconds()>=360) SinClock.restart();
        for(int i=0;i<bullets.size();i++) bullets[i].draw(window,adr,SinClock.getElapsedTime().asMicroseconds());
        for(int i=0;i<allalians;i++) aliens[i].draw(window);
        window->draw(ship);
        window->draw(boost,&BoostShader);
        window->draw(overheat,&BoostShader);
        score.setPosition(10,10);
        score.setString("SCORE: "+std::to_string(count));
        window->draw(score);
        score.setPosition(700,10);
        score.setString("LIVES: "+std::to_string(lives));
        window->draw(score);
    }
    
    ~player(){}
};
