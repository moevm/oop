#include "game.h"

#include <SFML/Graphics.hpp>
#include <iostream>

#include "field.h"
#include "object.h"

Game::Game(unsigned int width, unsigned int height)
{
    settings = new sf::ContextSettings;
    settings->antialiasingLevel = 8;

    r_window = new sf::RenderWindow(sf::VideoMode(width, height),
                                    "Game",
                                    sf::Style::Default,
                                    *settings);
    r_window->setFramerateLimit(60);
    view = new sf::View(sf::FloatRect(0.f, 0.f, r_window->getSize().x, r_window->getSize().y));
    r_window->setView(*view);
    r_window->setKeyRepeatEnabled(false);

    mouse = new sf::Mouse;
    old_mouse_pos = mouse->getPosition(*r_window);
    new_mouse_pos = mouse->getPosition(*r_window);

    mainFont = new sf::Font;
    mainFont->loadFromFile("arial.ttf");

    field = new Field(20, 20);
    turn = Red;
}


void Game::start(){
    sf::Event event;
    while(r_window->isOpen()){
        while(r_window->pollEvent(event)){
            distributeEvent(event);
        }
        handleKeyboardHeld();

        r_window->clear();

        field->draw(r_window);
        field->lightSpotedUnit(r_window);
        field->lightPossibleWays(r_window);

        auto window_pos = mouse->getPosition(*r_window);
        auto field_pos = field->getPointFromPixels(r_window, window_pos.x, window_pos.y);
        field->spotCell(r_window, field_pos.x, field_pos.y, CELLS);

        drawInterface();

        r_window->display();
    }
}


void Game::nextPlayer(){
    if (turn == Red)
        turn = Blu;
    else
        turn = Red;
    player++;
    if(player == 2){
        field->refresh();
        player = 0;
    }
}


void Game::distributeEvent(const sf::Event &event){
    if(event.type == sf::Event::Closed){
        r_window->close();
    }

    if(event.type == sf::Event::Resized){
        view->setSize(r_window->getSize().x, r_window->getSize().y);
        r_window->setView(*view);
    }

    if(event.type == sf::Event::MouseButtonPressed){
        handleMousePressEvent(event);
    }

    if(event.type == sf::Event::MouseButtonReleased){
        handleMouseReleaseEvent(event);
    }

    if(event.type == sf::Event::MouseMoved){
        handleMouseMoveEvent(event);
    }

    if(event.type == sf::Event::KeyPressed){
        handleKeyboardPressedEvent(event);
    }

    if(event.type == sf::Event::KeyReleased){
        handleKeyboardReleaseEvent(event);
    }

}


void Game::handleKeyboardPressedEvent(const sf::Event &event){
    switch (event.key.code) {
    case sf::Keyboard::U:
        nextPlayer();
        field->clearSelection();
        break;

    case sf::Keyboard::P:
        if(turn == Red)
            std::cout << "Red" << std::endl;
        else
            std::cout << "Blu" << std::endl;
        break;

    case sf::Keyboard::T:
        std::cout << field->turnsPassed() << std::endl;
        break;

    default: break;
    }
}


void Game::handleKeyboardReleaseEvent(const sf::Event &event){

}


void Game::handleKeyboardHeld(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        view->move(-10, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        view->move(10, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        view->move(0, -10);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        view->move(0, 10);
    }
}


void Game::handleMousePressEvent(const sf::Event &event){
    if(event.mouseButton.button == sf::Mouse::Button::Left){
        m_pressed = 1;
        old_mouse_pos = mouse->getPosition(*r_window);
        press_mouse_pos = old_mouse_pos;
    }
}


void Game::handleMouseReleaseEvent(const sf::Event &event){
    if(event.mouseButton.button == sf::Mouse::Button::Left){
        m_pressed = 0;

        auto window_pos = mouse->getPosition(*r_window);
        auto field_pos = field->getPointFromPixels(r_window, window_pos.x, window_pos.y);

        if(mouse->getPosition(*r_window) == press_mouse_pos){

            if(turn == Blu)
                field->spotUnit(Object::Blu, field_pos.x, field_pos.y, CELLS);
            else
                field->spotUnit(Object::Red, field_pos.x, field_pos.y, CELLS);

            field->moveSpottedUnit(field_pos.x, field_pos.y, CELLS);


            if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::B)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
                        field->createUnit("BluBarbarian", field_pos.x, field_pos.y, CELLS);
                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
                        field->createUnit("BluArcher", field_pos.x, field_pos.y, CELLS);
                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
                        field->createUnit("BluBerserker", field_pos.x, field_pos.y, CELLS);
                    std::cout << "createBlu" << std::endl;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
                        field->createUnit("RedBarbarian", field_pos.x, field_pos.y, CELLS);
                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
                        field->createUnit("RedArcher", field_pos.x, field_pos.y, CELLS);
                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
                        field->createUnit("RedBerserker", field_pos.x, field_pos.y, CELLS);
                    std::cout << "createRed" << std::endl;
                }
            }
        }
    }
    if(event.mouseButton.button == sf::Mouse::Button::Right){
        if(mouse->getPosition(*r_window) == press_mouse_pos){
            auto window_pos = mouse->getPosition(*r_window);
            auto field_pos = field->getPointFromPixels(r_window, window_pos.x, window_pos.y);
            field->deleteUnit(field_pos.x, field_pos.y, CELLS);
        }
        std::cout << "RClick" << std::endl;
    }
}


void Game::handleMouseMoveEvent(const sf::Event &event){
    if (m_pressed){
        new_mouse_pos.x = event.mouseMove.x;
        new_mouse_pos.y = event.mouseMove.y;

        view->move(old_mouse_pos.x - new_mouse_pos.x, old_mouse_pos.y - new_mouse_pos.y);
        r_window->setView(*view);

        old_mouse_pos = new_mouse_pos;
    }
}


void Game::drawInterface(){
    r_window->setView(r_window->getDefaultView());
    sf::Text text("Interface", *mainFont);
    text.setCharacterSize(80);
    text.setOutlineThickness(2);
    text.setOutlineColor(sf::Color::White);
    text.setFillColor(sf::Color::Black);
    text.setPosition(0, r_window->getSize().y - 100);
    r_window->draw(text);
    r_window->setView(*view);
}








