#ifndef GAMEINTERFACEBUTTON_H
#define GAMEINTERFACEBUTTON_H

#include <string>

namespace sf {
    class Texture;
    class RenderWindow;
}

class GameInterfaceButton
{
    const std::string button_id;    // unic name
    const std::string name;         // displaying name

    const sf::Texture& idle_texture;
    const sf::Texture& pressed_texture;

    float timeToLive;   // as ms
    float timer;        // as ms
    bool pressed;
    bool timeOut;

public:
    GameInterfaceButton(const GameInterfaceButton&) = delete;
    GameInterfaceButton(const GameInterfaceButton&&) = delete;
    GameInterfaceButton& operator=(const GameInterfaceButton&) = delete;

    GameInterfaceButton(const std::string& button_id,
                        const std::string& button_name,
                        const sf::Texture& idle_texture,
                        const sf::Texture& pressed_texture);

    void setTimeToLive(float timeToLive);

    const std::string& getID() const;
    const std::string& getName() const;

    void update(float time);
    void reset();

    void press();
    void release();

    bool isPressed() const;

    bool isTimedOut();

    void draw(sf::RenderWindow& window,
              float pos_x, float pos_y);

    int getRadius() const;
};

#endif // GAMEINTERFACEBUTTON_H
