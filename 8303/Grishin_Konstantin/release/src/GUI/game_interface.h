#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include <string>
#include <vector>
#include <SFML/System/Vector2.hpp>

#include "game_interface_button.h"

namespace sf {
    class Texture;
    class RenderWindow;
}


class GameInterface
{
    struct ButtonLocator{
        GameInterfaceButton &button;
        sf::Vector2f pos;
    };

    const std::string id;
    const std::string name;

    const sf::Texture &texture;

    GameInterface* parent = nullptr;
    std::vector<GameInterface*> successors;

    std::vector<ButtonLocator*> buttons;

    GameInterface *subInterface;

public:
    GameInterface(const std::string& interface_id,
                  const std::string& interface_name,
                  const sf::Texture& texture,
                  GameInterface * parent = nullptr);
    ~GameInterface();

    void addParent(GameInterface * parent);
    void addSuccessor(GameInterface * successor);

    void goDown(const std::string& subInterface);

    void addButton(GameInterfaceButton& button, float x, float y);
    const GameInterfaceButton& getButton(const std::string& button_id) const;

    void update(float time);
    void reset();
    void draw(sf::RenderWindow &renderWindow);

    int click(float x, float y, std::string& recieved_button, bool reset_other = 0);

    std::vector<std::string> getPressedButtons() const;

    sf::Vector2u getSize() const;

    const std::string& getID() const;
    const std::string& getName() const;
};

#endif // GAMEINTERFACE_H
