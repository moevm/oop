#ifndef GAME_ELEMENTS_H
#define GAME_ELEMENTS_H

#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "point.h"
#include "units.h"
#include "cells.h"


#define PIXELS 0
#define CELLS 1

namespace sf {
    class RenderTarget;
    class Event;
    class Color;
}


class Field{
public:
    enum Show{
        Moving,
        Attack
    };

private:
    sf::RenderTarget *target;
    int cell_size;

    int iWidth;
    int iHeight;
    int iMaxUnits;

    int iCurrentStep = 0;

    Cell **cell_arr;

    std::vector<Entity*> entities;
    std::vector<Point> possible_way;
    std::vector<Point> attack_area;

    Show spotlight = Moving;

    void findPossibleWay();
    void findAttackArea();

public:
    explicit Field(sf::RenderTarget *target, int width, int height);
    ~Field();

    void addUnit(Entity *unit);

    int getWidth() const;
    int getHeight() const;

    void draw();

    void spotCell(int x, int y, const sf::Color &color, int units = 0);
    void selectUnit(int x, int y, int units = 0);
    void lighDirections();
    void changeSpotlight();
    void moveSelectedUnit(int x, int y, int units = 0);
    void handleKeyboard(const sf::Event &event);
    void nextStep();



    std::string getData() const;

    friend auto operator<<(std::ostream &os, const Field &self){
        for(auto entity: self.entities){
            os << "Attack type: " << entity->attackType() << '\n';
            os << "Unit type: " << entity->unitType() << '\n';
            os << "Position: " << entity->pos().x << "; " << entity->pos().y << '\n';
            os << "Health: " << entity->health() << '\n';
            os << '\n';
        }
    }

    bool checkSteps() const;
};


#endif // GAME_ELEMENTS_H
