#ifndef MENUELEMENT_H
#define MENUELEMENT_H

#include <SFML/Graphics/Color.hpp>

#include <string>

namespace sf {
    class RenderWindow;
    class Font;
}

class Menu;

class MenuElement
{
    friend class Menu;
public:
    enum Type{
        Entry,
        EventButton,
        Checkbox,
        Slider
    };

private:
    const std::string option;
    const Type type;
    const sf::Color regular;
    const sf::Color chosen;
    bool isActive = 1;

    union{
        float value;
        bool pressed;
        Menu* subMenu;
    };

    MenuElement(const std::string& name,
                Type type,
                const sf::Color& regular,
                const sf::Color& chosen,
                Menu* subMenu = nullptr);

    void draw(sf::RenderWindow& window,
              const sf::Font& font,
              unsigned int font_size,
              float pos_x, float pos_y,
              bool chosen);

    void pressButton();
    void increaseVal(float val);
    void decreaseVal(float val);

    void setActive(bool active);
    bool active() const;

    bool checkPointInhere(int x, int y);
};

#endif // MENUELEMENT_H
