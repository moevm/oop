#include "pause_screen.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

PauseScreen::PauseScreen(sf::RenderWindow &window):
    window(window)
{}


void PauseScreen::draw(){
    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::Text pause("PAUSE", font, 60);
    pause.setOutlineThickness(4);
    pause.setOutlineColor(sf::Color::Black);
    pause.setFillColor(sf::Color::White);

    auto bounds = pause.getGlobalBounds();
    pause.setOrigin(bounds.width/2.f, bounds.width/2.f);

    sf::RectangleShape back(sf::Vector2f(bounds.width+40, bounds.height*2.5f));
    back.setOrigin(back.getSize().x/2.f, back.getSize().y/2.f);
    back.setOutlineThickness(6);
    back.setOutlineColor(sf::Color::Black);
    back.setFillColor(sf::Color(0x7F, 0x7F, 0x7F, 0x7F));

    back.setPosition(window.getSize().x/2.f, window.getSize().y/2.f);
    pause.setPosition(back.getPosition() + sf::Vector2f(0, back.getSize().y/4.f));

    sf::Text button("save and exit", font, 30);
    button.setOutlineThickness(2);
    button.setOutlineColor(sf::Color::Black);

    if(on_button){
        button.setFillColor(sf::Color::Cyan);
    } else {
        button.setFillColor(sf::Color::White);
    }

    auto button_bounds = button.getGlobalBounds();
    button.setOrigin(button_bounds.width/2.f, button_bounds.height/2.f);
//    button.setPosition(back.getPosition());
    button.setPosition(back.getPosition() + sf::Vector2f(0, button_bounds.height));

    pos = button.getPosition();
    size = sf::Vector2f(button_bounds.width, button_bounds.height);

    auto old_view = window.getView();
    sf::View new_view(sf::Vector2f(window.getSize().x/2.f, window.getSize().y/2.f),
                      sf::Vector2f(window.getSize()));
    window.setView(new_view);

    window.draw(back);
    window.draw(pause);
    window.draw(button);

    window.setView(old_view);

}


void PauseScreen::handleEvent(const sf::Event &event){
    if(event.type == sf::Event::KeyPressed)
        if(event.key.code == sf::Keyboard::Enter){
            save_and_exit = 1;
            return;
        }

        if(event.key.code == sf::Keyboard::Escape)
        {
            close = 1;
        }
    if(event.type == sf::Event::MouseButtonPressed){
        if(event.mouseButton.button == sf::Mouse::Left){
            auto x = event.mouseButton.x;
            auto y = event.mouseButton.y;

            if(x > pos.x - size.x/2.f && x < pos.x + size.x/2.f
            && y > pos.y - size.y/2.f && y < pos.y + size.y/2.f)
            {
                save_and_exit = 1;
                return;
            }
        }
    }

    if(event.type == sf::Event::MouseMoved){
        auto x = event.mouseMove.x;
        auto y = event.mouseMove.y;

        if(x > pos.x - size.x/2.f && x < pos.x + size.x/2.f
        && y > pos.y - size.y/2.f && y < pos.y + size.y/2.f)
        {
            on_button = 1;
        }
        else
            on_button = 0;
    }

}


bool PauseScreen::close_p() const{
    return close;
}


bool PauseScreen::save_and_exit_p() const{
    return save_and_exit;
}





