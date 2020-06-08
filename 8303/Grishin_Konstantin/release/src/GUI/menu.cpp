#include "GUI/menu.h"

#include "SFML/Graphics.hpp"

// set colors of menu, font and update target
Menu::Menu(sf::RenderWindow& window,
           const sf::Color& back,
           const sf::Color& choosen,
           const sf::Color& regular):
    window(window), clr_back(back), clr_choosen(choosen), clr_regular(regular)
{
    updateTarget();
    font.loadFromFile("arial.ttf");
}


// recalculate drawing parameters
// size of window, size of option line, etc...
void Menu::updateTarget()
{
    width = int(window.getSize().x);
    height = int(window.getSize().y);

    if(width < 800 || height < 600){
        font_size = 1;
    }
    else{
        float option_size = float(height)/(options.size()+2); // 2 fictive spacings on top and bottom
        top_offset = option_size;
        if(option_size > 80) option_size = 80;
        font_size = option_size; // probably should multiply on font size modifier
    }
}


void Menu::draw()
{
    //if there is subMenu, draw it
    if(subMenu){
        subMenu->draw();
    }
    //else draw own menu
    else{
        window.clear(clr_back);
        for(size_t i = 0; i < options.size(); i++){
            bool chosen = (i == unsigned(iCurrOption));
            options[i]->draw(window, font, unsigned(font_size), left_spacing, top_offset*(i+1), chosen);
        }
    }
}


// add new option line in option list
// and update its drawing parameters
void Menu::addOption(const std::string& op, MenuElement::Type type, bool active, Menu* subMenu)
{
    options.push_back(new MenuElement(op, type, clr_regular, clr_choosen, subMenu));
    options.back()->setActive(active);
    subMenuMap[op] = subMenu;
    if(subMenu){
        subMenu->parentMenu = this;
    }
    updateTarget();
}


// distribute event to handlers
int Menu::handleEvent(const sf::Event &event)
{
    if(subMenu){
        subMenu->handleEvent(event);
    }
    else{
        if (event.type == sf::Event::KeyPressed){
            handleKeyboard(event);
        }
        if (event.type == sf::Event::MouseMoved){
            handleMouse(event);
        }
        if(event.type == sf::Event::MouseButtonPressed){
            if(event.mouseButton.button == sf::Mouse::Left)
                if(options[iCurrOption]->active())
                    pressCurrentButton();
        }
        if(event.type == sf::Event::Resized){
            auto view = window.getDefaultView();
            view.setSize(event.size.width, event.size.height);
            window.setView(view);
            updateTarget();
        }
    }
    return 0;
}


void Menu::handleKeyboard(const sf::Event &event)
{
    if(event.key.code == sf::Keyboard::Escape){
        if(parentMenu) parentMenu->subMenu = nullptr;
    }

    if(event.key.code == sf::Keyboard::Enter){
        if(options[iCurrOption]->active())
            pressCurrentButton();
    }

    if(event.key.code == sf::Keyboard::Up){
        iCurrOption--;
    }
    if(event.key.code == sf::Keyboard::Down){
        iCurrOption++;
    }

    if(event.key.code == sf::Keyboard::Left){
        options[unsigned(iCurrOption)]->decreaseVal(5.f);
    }

    if(event.key.code == sf::Keyboard::Right){
        options[unsigned(iCurrOption)]->increaseVal(5.f);
    }

    if(iCurrOption < 0) iCurrOption = 0;

    if(iCurrOption >= int(options.size())) iCurrOption = int(options.size()) - 1;
}


void Menu::handleMouse(const sf::Event &event)
{
    auto pos_y = event.mouseMove.y;

    int line_number = int(pos_y/top_offset);
    line_number--;
    if(line_number >= 0 && line_number < int(options.size())){
        iCurrOption = line_number;
    }
}


void Menu::pressCurrentButton()
{
    options[unsigned(iCurrOption)]->pressButton();
    if(options[unsigned(iCurrOption)]->type == MenuElement::Entry){
        subMenu = options[unsigned(iCurrOption)]->subMenu;
    }
}


void Menu::recStateParser(MenuState &menuState){
    for(auto op: options){
        if(op->type == MenuElement::Entry)
            op->subMenu->recStateParser(menuState);
        if(op->type == MenuElement::Checkbox){
            std::string option_name = "b]" + op->option;
            menuState.settings[option_name] = op->pressed;
        }
        if(op->type == MenuElement::Slider){
            std::string option_name = "s]" + op->option;
            menuState.settings[option_name] = op->value;
        }
        if(op->type == MenuElement::EventButton){
            if(op->pressed){
                menuState.event_pressed = op->option;
            }
            op->pressed = 0;
        }
    }
}


void Menu::getState(MenuState &menuState)
{
    menuState.event_pressed = "";
    menuState.settings.clear();
    recStateParser(menuState);
}






