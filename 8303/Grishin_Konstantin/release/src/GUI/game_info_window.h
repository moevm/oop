#ifndef GAMEINFOWINDOW_H
#define GAMEINFOWINDOW_H

#include <SFML/System/Vector2.hpp>

#include <string>
#include <map>

namespace sf {
    class RenderWindow;
    class Font;
}

class GameInfoWindow
{
    std::string info;
    sf::RenderWindow &window;
    sf::Font* font;

    sf::Vector2f size;

public:
    GameInfoWindow(sf::RenderWindow &window, const std::string& info_string);
    ~GameInfoWindow();

    void draw(float x, float y, int alpha = 0xFF);
    const sf::Vector2f& getSize() const;
};

#endif // GAMEINFOWINDOW_H
