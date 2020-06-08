
#include <SFML/Graphics.hpp>
#include <iostream>

#include "GUI/menu.h"
#include "GUI/pause_screen.h"
//#include "game.h"
#include "t_game.h"
#include "game_elements/level.h"

#include "Rules/easy.h"


bool file_exist(const std::string& name){
    std::ifstream f(name);
    return f.good();
}


int main()
{
    unsigned int width = 800;
    unsigned int height = 600;

    auto settings =  new sf::ContextSettings;
    auto window = new sf::RenderWindow(sf::VideoMode(width, height),
                                       "Game",
                                       sf::Style::Default, *settings);
    window->setFramerateLimit(60);

    /// Start menu initializing, should be put into menu manager
    auto SubMenu = new Menu(*window, sf::Color(0, 0, 0),
                            sf::Color(0xEB, 0x09, 0x68),
                            sf::Color(0x72, 0x00, 0x30));

    SubMenu->addOption("Sound", MenuElement::Slider);
    SubMenu->addOption("Tips", MenuElement::Checkbox);

    auto MainMenu = new Menu(*window, sf::Color(0, 0, 0),
                             sf::Color(0xEB, 0x09, 0x68),
                             sf::Color(0x72, 0x00, 0x30));

    MainMenu->addOption("Continue", MenuElement::EventButton, file_exist("game_save.sv"));
    MainMenu->addOption("New Game", MenuElement::EventButton);
    MainMenu->addOption("Settings", MenuElement::Entry, 1, SubMenu);
    MainMenu->addOption("Quit", MenuElement::EventButton);
    MenuState menuState;
    /// END OF MENU INITIALIZING


    TGame<Easy> *game = nullptr;
    Easy rule(Team::Neutral);
    PauseScreen *pause = nullptr;


    sf::Event event;
    sf::Clock timer;
    sf::View old_view;
    while(window->isOpen()){
        float time = float(double(timer.getElapsedTime().asMicroseconds())/1000.f); // get milliseconds
        timer.restart();

        while(window->pollEvent(event)){
            // several events must be handled here
            if(event.type == sf::Event::Closed){
                window->close();
            }
            if(event.type == sf::Event::Resized){
                auto view = window->getView();
                view.setSize(event.size.width, event.size.height);
            }

            if(game && event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::P){
                    pause = new PauseScreen(*window);
                }
            }

            if(pause)
                pause->handleEvent(event);
            else if(game)
                game->handleEvent(event);
            else
                MainMenu->handleEvent(event);
        }
        window->clear();

        if(pause)
        {
            game->draw();
            pause->draw();
            if(pause->close_p()){
                delete pause;
                pause = nullptr;
            }
            else if(pause->save_and_exit_p()){
                delete pause;
                pause = nullptr;
                game->save("game_save.sv");
                delete game;
                game = nullptr;

                window->setView(old_view);
            }
        }
        else if(game)
        {
            //if game itialized and constructed handle game
            // ...
            game->frameStep(time);
            game->draw();

            if(game->gameFinished()){
                auto winner = game->getWinner();
                if(winner == Team::Red)
                    std::cout << "Red wins" << std::endl;
                else if(winner == Team::Blu)
                    std::cout << "Blu wins" << std::endl;
                else if(winner == Team::Neutral)
                    std::cout << "Game ended in a draw!" << std::endl;

                delete game;
                game = nullptr;

                window->setView(old_view);
            }

        }
        else
        {
            // handle menu
            MainMenu->getState(menuState);
            if(menuState.event_pressed == "Quit"){
                window->close();
                for(auto setting: menuState.settings){
                    std::cout << setting.first << ": " << setting.second << std::endl;
                }
            }

            if(menuState.event_pressed == "New Game"){
                old_view = window->getView();
                game = new TGame(*window, Level::default_level_1(), rule);
            }

            if(menuState.event_pressed == "Continue")
            {
                old_view = window->getView();

                try{
                    Level level("game_save.sv");
                    game = new TGame(*window, level, rule);
                }
                catch(Level::failure e)
                {
                    std::cout << e.what() << std::endl;
                    game = new TGame(*window, Level::default_level_1(), rule);
                }
            }
            MainMenu->draw();
        }

        window->display();
    }
    return 0;
}
