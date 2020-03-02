#ifndef GAME_H
#define GAME_H

#include "point.h"
#include "SFML/System/Vector2.hpp"

namespace sf {
    class RenderWindow;
    class ContextSettings;
    class View;
    class Event;
    class Mouse;
    class Font;
}

class Field;
class Player;
class BluPlayer;
class RedPlayer;


class Game
{
public:
    enum Turn{
        Blu,
        Red
    };

private:
    //========graphics================//
    sf::RenderWindow *r_window;
    sf::ContextSettings *settings;
    sf::View *view;
    sf::Font *mainFont;
    //================================//

    //========mouse===================//
    sf::Mouse *mouse;
    sf::Vector2i old_mouse_pos;
    sf::Vector2i press_mouse_pos;
    sf::Vector2i new_mouse_pos;
    bool m_pressed = 0;
    //================================//

    int player = 0;
    Turn turn;

    Field *field;

    void nextPlayer();

    void distributeEvent(const sf::Event &event);

    void handleKeyboardPressedEvent(const sf::Event &event);
    void handleKeyboardReleaseEvent(const sf::Event &event);
    void handleKeyboardHeld();

    void handleMousePressEvent(const sf::Event &event);
    void handleMouseReleaseEvent(const sf::Event &event);
    void handleMouseMoveEvent(const sf::Event &event);

    void drawInterface();

public:
    Game(unsigned int width, unsigned int height);
    void start();
};

#endif // GAME_H
