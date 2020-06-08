#include "GUI/menu_element.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

MenuElement::MenuElement(const std::string& name,
                         Type type,
                         const sf::Color& regular,
                         const sf::Color& chosen,
                         Menu* subMenu):
    option(name), type(type), regular(regular), chosen(chosen)
{
    switch (type){
    case Type::Slider:
        this->value = 0;
        break;

    case Type::Checkbox:
        this->pressed = 0;
        break;

    case Type::EventButton:
        this->pressed = 0;
        break;

    case Type::Entry:
        if(subMenu == nullptr)
            throw 0x010;
        this->subMenu = subMenu;
        break;
    }
}


void MenuElement::draw(sf::RenderWindow &window,
                       const sf::Font &font,
                       unsigned int font_size,
                       float pos_x, float pos_y,
                       bool chosen)
{
    if(!isActive)
        chosen = 0;

    sf::Text option_line(option, font, unsigned(font_size));
    option_line.setPosition(pos_x, pos_y);

    option_line.setFillColor((chosen)?this->chosen:this->regular);
    window.draw(option_line);

    if(type == Type::Checkbox){
        sf::RectangleShape checkbox(sf::Vector2f(float(font_size)/8.f*7.f,
                                                 float(font_size)/8.f*7.f));
        checkbox.setPosition(pos_x+option_line.getGlobalBounds().width+40+float(font_size)/8.f,
                                   pos_y+float(font_size)/8.f);
        checkbox.setFillColor(sf::Color(0,0,0,0));
        checkbox.setOutlineThickness(float(font_size)/8.f);
        checkbox.setOutlineColor((chosen)?this->chosen:this->regular);
        window.draw(checkbox);

        if(pressed){
            sf::RectangleShape inner_square(sf::Vector2f(float(font_size)/8.f*5.f,
                                                         float(font_size)/8.f*5.f));
            inner_square.setOrigin(inner_square.getSize().x/2.f,
                                   inner_square.getSize().y/2.f);
            inner_square.setPosition(checkbox.getPosition().x+checkbox.getSize().x/2.f,
                                     checkbox.getPosition().y+checkbox.getSize().y/2.f);
            inner_square.setFillColor((chosen)?this->chosen:this->regular);
            window.draw(inner_square);
        }
    }
    if(type == Type::Slider){
        sf::RectangleShape filled_part(sf::Vector2f(value*2, font_size/8.f*6.f));
        filled_part.setPosition(pos_x + option_line.getGlobalBounds().width + 40,
                                pos_y + float(font_size)/8.f);
        filled_part.setFillColor((chosen)?this->chosen:this->regular);

        sf::RectangleShape empty_part(sf::Vector2f((100-value)*2, font_size/8.f*6.f));
        empty_part.setPosition(filled_part.getPosition().x + filled_part.getSize().x,
                               filled_part.getPosition().y);
        empty_part.setFillColor((chosen)?this->chosen:this->regular - sf::Color(0, 0, 0, 0x60));

        window.draw(filled_part);
        window.draw(empty_part);
    }

    if(type == Type::Entry){
        sf::ConvexShape triangle;
        triangle.setPointCount(3);
        triangle.setPoint(0, sf::Vector2f(pos_x + option_line.getGlobalBounds().width + 40,
                                          pos_y + float(font_size)/4.f));
        triangle.setPoint(1, sf::Vector2f(pos_x + option_line.getGlobalBounds().width + 40 + 30,
                                          pos_y + float(font_size)/2.f));
        triangle.setPoint(2, sf::Vector2f(pos_x + option_line.getGlobalBounds().width + 40,
                                          pos_y + float(font_size)/4.f*3.f));
        triangle.setFillColor((chosen)?this->chosen:this->regular);
    }
}


void MenuElement::pressButton(){
    if(type == Type::Checkbox || type == Type::EventButton)
        pressed = !pressed;
}


void MenuElement::increaseVal(float val){
    if(type == Type::Slider){
        value += val;
        if(value > 100) value = 100;
    }
}


void MenuElement::setActive(bool active){
    isActive = active;
}


bool MenuElement::active() const
{
    return isActive;
}


void MenuElement::decreaseVal(float val){
    if(type == Type::Slider){
        value -= val;
        if(value < 0) value = 0;
    }
}





