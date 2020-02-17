#include "cells.h"
#include <SFML/Graphics.hpp>

Cell::Cell(){
    this->type = Type::open;
}


Cell::Type Cell::getType() const{
    return type;
}


void Cell::draw(sf::RenderTarget *target, Point position, int size){
    int outline = 3;

    sf::RectangleShape cell_shape(sf::Vector2f(size, size));
    cell_shape.setOutlineThickness(outline);
    cell_shape.setOutlineColor(sf::Color::Black);
    cell_shape.setFillColor(sf::Color::Cyan);

    cell_shape.setPosition(sf::Vector2f(outline + position.x * (outline + size), outline + position.y * (outline + size)));

    target->draw(cell_shape);
}
