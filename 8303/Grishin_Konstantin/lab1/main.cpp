// simple cells +
// field +


#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#include "field.h"


int main()
{
    //create game window
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(800, 600), "4semproj");
    sf::RenderWindow *data = new sf::RenderWindow(sf::VideoMode(600, 600), "datawindow");
    sf::Event event;

    sf::Mouse *mouse = new sf::Mouse;

    window->setFramerateLimit(60);

    //initialize game field
    Field *game_field = new Field(window, 12, 12);

    Melee *test1 = new Melee(Point{ 2, 2}, 20, 10, 3);
    game_field->addUnit(dynamic_cast<Entity*>(test1));

    Range *test2 = new Range(Point{ 7, 7}, 15, 2, 2, 5);
    game_field->addUnit(dynamic_cast<Entity*>(test2));

    Absent *test3 = new Absent(Point{2,5}, 17, 4);
    game_field->addUnit(test3);

    game_field->changeSpotlight();
    game_field->changeSpotlight();

    std::stringstream datastream;

    //main cycle
    while(window->isOpen())
    {
        while(window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window->close();
            if(event.type == sf::Event::MouseButtonPressed){
                game_field->selectUnit(mouse->getPosition(*window).x, mouse->getPosition(*window).y, PIXELS);
                game_field->moveSelectedUnit(mouse->getPosition(*window).x, mouse->getPosition(*window).y, PIXELS);
            }
            if(event.type == sf::Event::KeyPressed){
                game_field->handleKeyboard(event);
            }
        }

        window->clear();

        game_field->draw();

        game_field->lighDirections();

        game_field->spotCell(mouse->getPosition(*window).x, mouse->getPosition(*window).y, sf::Color(255, 255, 255, 200));

        window->display();

        data->clear();

        sf::Font font;
        font.loadFromFile("arial.ttf");

        sf::Text out(game_field->getData(), font);
        data->draw(out);
        data->display();
    }

    data->close();

    delete game_field;
    delete window;
    delete data;
}





















