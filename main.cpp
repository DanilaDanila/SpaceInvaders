
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// In order to load the resources like cute_image.png, you have to set up
// your target scheme:
//
// - Select "Edit Scheme…" in the "Product" menu;
// - Check the box "use custom working directory";
// - Fill the text field with the folder path containing your resources;
//        (e.g. your project folder)
// - Click OK.
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <CoreFoundation/CoreFoundation.h>
#include "gamemanager.cpp"
#include "menu.h"

std::string getadress()
{
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    char path[PATH_MAX];
    CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX);
    std::string adress=path;
    return adress;
}

int main(int argc, char const** argv)
{
    sf::RenderWindow window(sf::VideoMode(800,600),"Space Invaders");
    window.setFramerateLimit(60);
    
    bool ingame=false;
    bool lose=false;
    
    sf::Music music;
    sf::Font font;
    font.loadFromFile(getadress()+"/Arial.ttf");
    sf::Text letter;
    letter.setString("YOU LOSE");
    letter.setFont(font);
    letter.setCharacterSize(100);
    letter.setStyle(sf::Text::Bold);
    letter.setColor(sf::Color::Red);
    letter.setPosition(150,245);
    
    sf::SoundBuffer buffer;
    buffer.loadFromFile(getadress()+"/button.wav");
    sf::Sound sound;
    sound.setBuffer(buffer);
    
    menu menu;
    menu.setup(sound,getadress()+"/menu.wav",100,getadress());
    music.openFromFile(getadress()+"/menu.wav");
    music.setLoop(true);
    music.play();
    sf::Texture t;
    t.loadFromFile(getadress()+"/to_game.png");
    sf::Sprite s;
    s.setTexture(t);
    menu.createbutton(s,sf::IntRect(300,255,200,90),sf::Color(200,200,200),sf::Color::White);
    game igra;
    igra.setup(getadress());
    
    sf::Clock clock;
    float fon;
    float time;
    bool click=false;
    sf::Vector2i mpos;
    sf::Vector2f pos;
    
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type==event.Closed) window.close();
        }
        time=clock.getElapsedTime().asMicroseconds()/4000;
        clock.restart();
        fon+=0.004*time;
        if(fon==360) fon=0;
        window.clear();
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) igra.ship.dx=-1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) igra.ship.dx=1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) igra.ship.shoot=true;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) igra.ship.ifboost=true;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) && lose) {lose=false;igra.setup(getadress());}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && lose) {lose=false;ingame=false;menu.reboot();window.clear();}
        
        mpos=sf::Mouse::getPosition(window);
        pos=window.mapPixelToCoords(mpos);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) click=true;
        
        if(lose) time=0;
        if(!ingame) menu.draw(&window,pos,click,fon);
        if(menu.buttons[0].click) ingame=true;
        if(ingame)igra.gameloop(&window,time);
        if(igra.ship.lives==0) lose=true;
        if(lose) window.draw(letter);
        
        click=false;
        window.display();
    }
    return 0;
}
