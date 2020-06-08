#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H

#include <SFML/System/Vector2.hpp>

namespace sf {
    class RenderWindow;
    class Event;
}

class PauseScreen
{
    sf::RenderWindow &window;
    sf::Vector2f size;
    sf::Vector2f pos;

    bool close = 0;
    bool save_and_exit = 0;
    bool on_button = 0;

public:
    PauseScreen(sf::RenderWindow& window);
    void draw();

    void handleEvent(const sf::Event &event);

    bool close_p() const;
    bool save_and_exit_p() const;
};

#endif // PAUSESCREEN_H
