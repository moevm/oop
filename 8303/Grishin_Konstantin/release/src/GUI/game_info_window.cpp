#include "game_info_window.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <iostream>

GameInfoWindow::GameInfoWindow(sf::RenderWindow &window, const std::string& info_string):
    window(window)
{
    font = new sf::Font;
    font->loadFromFile("arial.ttf");
    info = info_string;
}


GameInfoWindow::~GameInfoWindow(){
    delete font;
}


void GameInfoWindow::draw(float x, float y, int alpha){
    sf::Text info_text(info, *font, 16);
    info_text.setOutlineThickness(1);
    info_text.setLineSpacing(1);

    info_text.setOutlineColor(sf::Color(0, 0, 0, alpha));
    info_text.setFillColor(sf::Color(0xFF, 0xFF, 0xFF, alpha));

    auto bounds(info_text.getGlobalBounds());

    sf::RectangleShape back(sf::Vector2f(bounds.width+6, bounds.height+6));
    size = back.getSize();
    back.setOutlineThickness(2);
    back.setOutlineColor(sf::Color(0, 0, 0, alpha));
    back.setFillColor(sf::Color(0x7F, 0x7F, 0x7F, alpha));

    back.setPosition(x-3 + bounds.left, y-3 + bounds.top);
    info_text.setPosition(x, y);

    sf::Vector2f back_offset(0, 0);
    sf::Vector2f text_offset(0, 0);

    if(y + back.getSize().y > window.getSize().y){
        back_offset += sf::Vector2f(0, -back.getSize().y);
        text_offset += sf::Vector2f(0, -back.getSize().y);
    }
    if(x + back.getSize().x > window.getSize().x){
        back_offset += sf::Vector2f(-back.getSize().x, 0);
        text_offset += sf::Vector2f(-back.getSize().x, 0);
    }

    info_text.move(text_offset);
    back.move(back_offset);

    window.draw(back);
    window.draw(info_text);
}


const sf::Vector2f& GameInfoWindow::getSize() const{
    return size;
}
