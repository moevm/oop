#include "game_interface.h"

#include <iostream>
#include <exception>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

GameInterface::GameInterface(const std::string& interface_id,
                             const std::string& interface_name,
                             const sf::Texture& texture,
                             GameInterface * parent):
    id(interface_id),
    name(interface_name),
    texture(texture),
    parent(parent),
    subInterface(nullptr)
{
    if(parent){
        parent->successors.push_back(this);
    }
}


GameInterface::~GameInterface(){
    for(auto successor: successors){
        successor->parent =  nullptr;
    }

    if(parent){
        for(auto it_brother = parent->successors.begin();
            it_brother != parent->successors.end();
            it_brother++){
            if ((*it_brother) == this){
                parent->successors.erase(it_brother);
                break;
            }
        }
    }
}


void GameInterface::addParent(GameInterface *parent){
    if(parent){
        this->parent = parent;
        parent->successors.push_back(this);
    }
}


void GameInterface::addSuccessor(GameInterface *successor){
    if(successor){
        successors.push_back(successor);
        successor->parent = this;
    }
}


void GameInterface::goDown(const std::string &subInterface){
    for(auto s: successors){
        if(s->id == subInterface){
            this->subInterface =  s;
            return;
        }
    }
}


void GameInterface::addButton(GameInterfaceButton &button, float x, float y){
    auto bl = new ButtonLocator{button, sf::Vector2f(x, y)};
    buttons.push_back(bl);
}


const GameInterfaceButton&
GameInterface::getButton(const std::string& button_id) const{
    for(auto button: buttons)
    {
        if(button->button.getID() == button_id)
            return button->button;
    }
    throw std::out_of_range("Trying to call non-existent button");
}


void GameInterface::update(float ms_time){
    for(auto bl: buttons){
        bl->button.update(ms_time);
    }

    // also can update whole interface
}


void GameInterface::reset(){
    for(auto b: buttons){
        b->button.reset();
    }
}


void GameInterface::draw(sf::RenderWindow &renderWindow){
    if(subInterface){
        subInterface->draw(renderWindow);
    }
    else{
        auto sprite = sf::Sprite(texture);
        float y_offset = renderWindow.getSize().y - sprite.getGlobalBounds().height;

        sprite.setPosition(0, y_offset);
        renderWindow.draw(sprite);

        for(auto bl: buttons){
            bl->button.draw(renderWindow, bl->pos.x, y_offset+bl->pos.y);
        }
    }
}


int GameInterface::click(float x, float y, std::string& recieved_button, bool reset_other){
    for(auto bl: buttons){
        if((bl->pos.x - x)*(bl->pos.x - x) + (bl->pos.y - y)*(bl->pos.y - y) <= bl->button.getRadius()*bl->button.getRadius()){
            recieved_button = bl->button.getID();

            if(bl->button.isPressed()){
                bl->button.release();
                return -1;
            }
            else{
                if(reset_other) reset();
                bl->button.press();
                return 1;
            }
        }
    }
    return 0;
}


std::vector<std::string>
GameInterface::getPressedButtons() const{
    std::vector<std::string> tokens;
    for(auto b: buttons){
        if(b->button.isPressed())
            tokens.emplace_back(b->button.getID());
    }
    return tokens;
}


sf::Vector2u GameInterface::getSize() const{
    return texture.getSize();
}


const std::string& GameInterface::getID() const{
    return id;
}


const std::string& GameInterface::getName() const{
    return name;
}




