/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Menu has four types of options:                                         *
 * Entry - goes deeper into menu, just like some settings menus in games   *
 * Slider - let you change some parameter of program through arrows        *
 * Checkbox - let you set some flag on true or false                       *
 * EventButton - should be handled thorugh MenuState in main cycle.        *
 *               or it can work just like checkbox without mark            *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>
#include <string>
#include <map>

#include "GUI/menu_state.h"
#include "GUI/menu_element.h"

class Menu
{
public:
    enum Allignment{
        Left,
        Middle,
        Right
    };

    static constexpr float left_spacing = 30.f;
    static constexpr float right_spacing = 30.f;

private:
    sf::RenderWindow &window;

    std::vector<MenuElement*> options;
    std::map<std::string, Menu*> subMenuMap;
    Menu* parentMenu = nullptr;
    Menu* subMenu = nullptr;

    int iCurrOption = 0;

    sf::Color clr_back;
    sf::Color clr_choosen;
    sf::Color clr_regular;
    sf::Font font;

    float font_size;
    int width;
    int height;
    Menu::Allignment allignment = Menu::Left;
    float top_offset;



private:
    void handleKeyboard(const sf::Event &event);
    void handleMouse(const sf::Event &event);
    void recStateParser(MenuState &menuState);

public:
    Menu(sf::RenderWindow& window,
         const sf::Color& back,
         const sf::Color& choosen,
         const sf::Color& regular);

    void draw();

    void updateTarget();
    void addOption(const std::string& op, MenuElement::Type type, bool active = 1, Menu* subMenu = nullptr);
    int handleEvent(const sf::Event &event);
    void pressCurrentButton();

    void getState(MenuState& menuState);

};

#endif // MENU_H
