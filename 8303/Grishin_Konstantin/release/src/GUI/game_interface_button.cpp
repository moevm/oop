#include "game_interface_button.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

GameInterfaceButton::GameInterfaceButton(const std::string& button_id,
                                         const std::string& button_name,
                                         const sf::Texture& idle_texture,
                                         const sf::Texture& pressed_texture):
    button_id(button_id),
    name(button_name),
    idle_texture(idle_texture),
    pressed_texture(pressed_texture),
    timeToLive(0.f),
    timer(0.f),
    pressed(0),
    timeOut(0)
{}


void GameInterfaceButton::setTimeToLive(float timeToLive)
{
    this->timeToLive = timeToLive;
}


const std::string& GameInterfaceButton::getID() const{
    return button_id;
}


const std::string& GameInterfaceButton::getName() const{
    return name;
}


void GameInterfaceButton::update(float ms_time)
{
    if(pressed && timeToLive > 0){
        timer += ms_time;
        if(timer > timeToLive){
            timeOut = 1;
            pressed = 0;
            timer = 0;
        }
    }
    else
    {
        timer = 0;
    }
}


void GameInterfaceButton::reset(){
    pressed = 0;
    timer = 0;
}


void GameInterfaceButton::press(){
    pressed = 1;
}


bool GameInterfaceButton::isPressed() const{
    return pressed;
}


void GameInterfaceButton::release(){
    if(timeToLive <= 0)
        pressed = 0;
}


bool GameInterfaceButton::isTimedOut()
{
    if(timeOut){
        timeOut = 1;
        return 1;
    }
    return 0;
}


void GameInterfaceButton::draw(sf::RenderWindow &window,
                               float pos_x, float pos_y)
{
    auto button_sprite = sf::Sprite();
    if(pressed)
        button_sprite.setTexture(pressed_texture, true);
    else
        button_sprite.setTexture(idle_texture, true);

    button_sprite.setOrigin(button_sprite.getGlobalBounds().width/2,
                            button_sprite.getGlobalBounds().height/2);
    button_sprite.setPosition(pos_x, pos_y);
    window.draw(button_sprite);
}


int GameInterfaceButton::getRadius() const{
    return idle_texture.getSize().x/2;
}













