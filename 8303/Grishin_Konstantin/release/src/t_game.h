#ifndef TGAME_H
#define TGAME_H


#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "game_elements/team.h"
#include "game_elements/interface/entity_interface.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>


#include "game_elements/field.h"
#include "GUI/resource_manager.h"
#include "GUI/game_interface_manager.h"
#include "GUI/game_info_window.h"
#include "GUI/splash_messages.h"

#include "game_elements/commands/commands_queue.h"
#include "game_elements/commands/concrete_commands.h"

#include "game_elements/buildings/base.h"
#include "game_elements/level.h"

#include "rand_int.h"
#include "logger.h"
#include "printer.h"


#define CELL_SELECTOR_SIZE 64

namespace sf {
    class RenderWindow;
    class Event;
}



template <class T>
class TGame
{
private:
    //Render place
    sf::RenderWindow &window;
    ResourceManager *resourceManager = nullptr;
    GameInterfaceManager *interfaceManager = nullptr;
    std::string currentInterface;
    GameInfoWindow *info;
    SplashMessages *splasher;


    // cursor tracker;
    int press_x = 0;
    int press_y = 0;
    int old_x = 0;
    int old_y = 0;
    float waiting_time = 0;

    //Field - complex container of units and cells
    Field* field;

    //Player turn
    Team turn = Team::Red;
    bool nextStep = 0;
    bool mouse_on_turn = 0;

    //Turns left
    int iTurnsLeft = 0;

    //Entities selected for interraction
    EntityInterface markedEntity;
    bool draw_ways = 0;
    bool draw_targets = 0;

    EntityInterface markedObject;

    //Commands handler
    CommandsQueue *cmd_list;

    //Game points
    int red_points = 1;
    int blu_points = 1;
    float points_mod = 1;

    Team winner = Team::Neutral;
    bool game_finished = 0;

    //Game rules
    T rules;

    //log data
    Logger *logger;
    std::ofstream ofs;

public:
    TGame(sf::RenderWindow &window, const Level& lvl, const T& rules):
        window(window),
        info(nullptr),
        markedEntity(nullptr),
        markedObject(nullptr),
        rules(rules)
    {
        logger = new Logger();
        Printer::init();
        ofs.open("game_log.log");

        auto view = window.getView();
        view.zoom(0.5f);
        window.setView(view);

        field = new Field(lvl, logger);

        resourceManager = new ResourceManager;
        interfaceManager = new GameInterfaceManager;
        cmd_list = new CommandsQueue;
        splasher = new SplashMessages;

        loadResources();
        initInterface();

        currentInterface = "main";

        RandInt randomizer;
        if(randomizer(0, 1) == 1){
            turn = Team::Red;
        } else {
            turn = Team::Blu;
        }

        this->rules.init(field, this);
    }


    ~TGame()
    {
        // if there is any logs in buffer,
        // print it
        Printer printer(*logger, ofs);
        printer.print();
        ofs.close();

        // free memory
        delete resourceManager;
        delete interfaceManager;
        delete cmd_list;
        delete field;
        delete logger;
        delete splasher;
    }


    void draw()
    {

        // draw cells;
        for(auto cellInterface: *field){
            cellInterface.draw(window, *resourceManager);
        }

        // spot cell under cursor
        selectCell();

        // draw entities
        for(auto cellInterface: *field){
            cellInterface.getEntity().draw(window, *resourceManager);
        }

        // draw attributes of marked_entites
        markedEntity.drawSelector(window, *resourceManager);

        if(draw_ways){
            for(auto &p: markedEntity.getWays())
            {
                sf::CircleShape point(15, 4);
                point.setOutlineThickness(2);
                point.setOutlineColor(sf::Color(0x2F, 0x6A, 0x31, 0xFF));
                point.setFillColor(sf::Color(0x60, 0x88, 0x51, 0x7F));

                point.setOrigin(point.getRadius(), point.getRadius());
                point.setPosition((p.first.x + 0.5f)*CELL_SELECTOR_SIZE,
                                  (p.first.y + 0.5f)*CELL_SELECTOR_SIZE);
                window.draw(point);
            }
        }

        if(draw_targets){
            for(auto &p: markedEntity.getTargets())
            {
                sf::Sprite cross(resourceManager->getTexture("cross"));
                cross.setOrigin(cross.getGlobalBounds().width/2.f,
                                cross.getGlobalBounds().height/2.f);

                cross.setPosition((p.x + 0.5f)*CELL_SELECTOR_SIZE,
                                  (p.y + 0.5f)*CELL_SELECTOR_SIZE);
                window.draw(cross);
            }
        }

        // rebound view and draw interface
        auto old_view = window.getView();
        auto interface_view = old_view;
        interface_view.zoom(2);
        interface_view.setCenter(window.getSize().x/2, window.getSize().y/2);
        window.setView(interface_view);
        drawInterface();
        window.setView(old_view);
    }


    void frameStep(float ms_time)
    {
        auto points = cmd_list->apply(logger);

        red_points += int(points.first * points_mod);
        blu_points += int(points.second * points_mod);

        Printer printer(*logger, ofs);
        printer.print();

        // update field
        field->update(ms_time);

        // update interface if it is
        if(!currentInterface.empty())
            interfaceManager->getInterface(currentInterface).update(ms_time);

        splasher->update(ms_time);

        // control interface changing
        if(!markedEntity.empty()){
            if(markedObject.empty()){
                if(currentInterface != markedEntity.getID())
                {
                    if(!currentInterface.empty()){
                        interfaceManager->getInterface(currentInterface).reset();
                    }

                    currentInterface = markedEntity.getID();
                }
            }
            else
            {
                if(currentInterface != markedObject.getID())
                {
                    if(!currentInterface.empty()){
                        interfaceManager->getInterface(currentInterface).reset();
                    }

                    currentInterface = markedObject.getID();
                }
            }
        }
        else
        {
            if(!currentInterface.empty()){
                interfaceManager->getInterface(currentInterface).reset();
                currentInterface.clear();
            }
        }
    }


    bool gameFinished() const
    {
        return game_finished;
    }


    Team getWinner() const
    {
        return winner;
    }


    void handleEvent(sf::Event& event)
    {
        if(event.type == sf::Event::MouseMoved)
            mouseMoveEvent(event.mouseMove.x, event.mouseMove.y);
        if(event.type == sf::Event::MouseButtonPressed){
            mousePressEvent(event.mouseButton.button,
                            event.mouseButton.x,
                            event.mouseButton.y);
        }
        if(event.type == sf::Event::MouseButtonReleased){
            mouseReleaseEvent(event.mouseButton.button,
                              event.mouseButton.x,
                              event.mouseButton.y);
        }
        if(event.type == sf::Event::Resized){
            resizeEvent(event.size.width, event.size.height);
        }
        if(event.type == sf::Event::KeyPressed){
            keyPressedEvent(event.key.code);
        }
    }


    void addPoints(Team team, int score)
    {
        if(team == Team::Red) red_points += score;
        if(team == Team::Blu) blu_points += score;
    }


    std::pair<int, int> getPoints() const
    {
        return std::pair(red_points, blu_points);
    }


    void setPointsMod(float mod)
    {
        points_mod = mod;
    }


    void setFirstPlayer(Team p)
    {
        if(p == Team::Neutral)
        {
            RandInt randomizer;
            if(randomizer(0, 1) == 1){
                p = Team::Red;
            } else {
                p = Team::Blu;
            }
        }

        turn = p;
    }


    void save(const std::string& name) const
    {
        auto lvl = field->save();
        lvl.saveToFile(name);
    }


private:
    void loadResources()
    {
        if(resourceManager == nullptr) return;

        //// LANDSCAPE
        resourceManager->loadTexture("landscape_plain", "resources/landscapes/landscape_plain.png");
        resourceManager->loadTexture("landscape_canyon", "resources/landscapes/landscape_canyon.png");
        resourceManager->loadTexture("landscape_rough", "resources/landscapes/landscape_rough.png");
        resourceManager->loadTexture("empty", "resources/landscapes/empty.png");

        //// INTERFACE
        resourceManager->loadTexture("game_interface", "resources/interface/game_interface.png");

        resourceManager->loadTexture("empty_button", "resources/interface/button.png", 1);
        resourceManager->loadTexture("pressed_empty_button", "resources/interface/button_pressed.png", 1);

        resourceManager->loadTexture("move_button", "resources/interface/move_button.png", 1);
        resourceManager->loadTexture("pressed_move_button", "resources/interface/pressed_move_button.png", 1);

        resourceManager->loadTexture("attack_button", "resources/interface/attack_button.png", 1);
        resourceManager->loadTexture("pressed_attack_button", "resources/interface/pressed_attack_button.png", 1);

        resourceManager->loadTexture("take_button", "resources/interface/take_button.png", 1);
        resourceManager->loadTexture("pressed_take_button", "resources/interface/pressed_take_button.png", 1);

        resourceManager->loadTexture("work_button", "resources/interface/work_button.png", 1);
        resourceManager->loadTexture("pressed_work_button", "resources/interface/pressed_work_button.png", 1);

        resourceManager->loadTexture("melee_button", "resources/interface/melee_button.png", 1);
        resourceManager->loadTexture("pressed_melee_button", "resources/interface/pressed_melee_button.png", 1);

        resourceManager->loadTexture("range_button", "resources/interface/range_button.png", 1);
        resourceManager->loadTexture("pressed_range_button", "resources/interface/pressed_range_button.png", 1);

        resourceManager->loadTexture("nuker_button", "resources/interface/nuker_button.png", 1);
        resourceManager->loadTexture("pressed_nuker_button", "resources/interface/pressed_nuker_button.png", 1);

        resourceManager->loadTexture("worker_button", "resources/interface/worker_button.png", 1);
        resourceManager->loadTexture("pressed_worker_button", "resources/interface/pressed_worker_button.png", 1);

        resourceManager->loadTexture("destroy_button", "resources/interface/destroy_button.png", 1);
        resourceManager->loadTexture("pressed_destroy_button", "resources/interface/pressed_destroy_button.png", 1);

        resourceManager->loadTexture("use_button", "resources/interface/use_button.png", 1);
        resourceManager->loadTexture("pressed_use_button", "resources/interface/pressed_use_button.png", 1);

        resourceManager->loadTexture("turn_button", "resources/interface/turn_button.png", 1);
        resourceManager->loadTexture("darker_turn_button", "resources/interface/darker_turn_button.png", 1);
        resourceManager->loadTexture("pressed_turn_button", "resources/interface/pressed_turn_button.png", 1);

        resourceManager->loadTexture("scores", "resources/interface/scores.png");

        //// UNITS
        resourceManager->loadTexture("red_unit_knight", "resources/units/redKnight.png");
        resourceManager->loadTexture("red_unit_troll", "resources/units/redTroll.png");
        resourceManager->loadTexture("red_unit_archer", "resources/units/redArcher.png");
        resourceManager->loadTexture("red_unit_atrons", "resources/units/redAtrons.png");
        resourceManager->loadTexture("red_unit_berserk", "resources/units/redBerserk.png");
        resourceManager->loadTexture("red_unit_wizard", "resources/units/redWizard.png");
        resourceManager->loadTexture("red_unit_worker", "resources/units/redWorker.png");

        resourceManager->loadTexture("outline_red_unit_knight", "resources/units/outline_red_knight.png");
        resourceManager->loadTexture("outline_red_unit_troll", "resources/units/outline_red_troll.png");
        resourceManager->loadTexture("outline_red_unit_archer", "resources/units/outline_red_archer.png");
        resourceManager->loadTexture("outline_red_unit_atrons", "resources/units/outline_red_atrons.png");
        resourceManager->loadTexture("outline_red_unit_berserk", "resources/units/outline_red_berserk.png");
        resourceManager->loadTexture("outline_red_unit_wizard", "resources/units/outline_red_wizard.png");
        resourceManager->loadTexture("outline_red_unit_worker", "resources/units/outline_red_worker.png");

        resourceManager->loadTexture("blu_unit_knight", "resources/units/bluKnight.png");
        resourceManager->loadTexture("blu_unit_troll", "resources/units/bluTroll.png");
        resourceManager->loadTexture("blu_unit_archer", "resources/units/bluArcher.png");
        resourceManager->loadTexture("blu_unit_atrons", "resources/units/bluAtrons.png");
        resourceManager->loadTexture("blu_unit_berserk", "resources/units/bluBerserk.png");
        resourceManager->loadTexture("blu_unit_wizard", "resources/units/bluWizard.png");
        resourceManager->loadTexture("blu_unit_worker", "resources/units/bluWorker.png");

        resourceManager->loadTexture("outline_blu_unit_knight", "resources/units/outline_blu_knight.png");
        resourceManager->loadTexture("outline_blu_unit_troll", "resources/units/outline_blu_troll.png");
        resourceManager->loadTexture("outline_blu_unit_archer", "resources/units/outline_blu_archer.png");
        resourceManager->loadTexture("outline_blu_unit_atrons", "resources/units/outline_blu_atrons.png");
        resourceManager->loadTexture("outline_blu_unit_berserk", "resources/units/outline_blu_berserk.png");
        resourceManager->loadTexture("outline_blu_unit_wizard", "resources/units/outline_blu_wizard.png");
        resourceManager->loadTexture("outline_blu_unit_worker", "resources/units/outline_blu_worker.png");

        resourceManager->loadTexture("cross", "resources/util/cross.png");
        resourceManager->loadTexture("killed", "resources/util/killed.png");

        //// BUILDINGS
        resourceManager->loadTexture("red_building_base_up", "resources/buildings/red_base_up.png");
        resourceManager->loadTexture("red_building_base_right", "resources/buildings/red_base_right.png");
        resourceManager->loadTexture("red_building_base_down", "resources/buildings/red_base_down.png");

        resourceManager->loadTexture("red_building_tower_up", "resources/buildings/red_tower_up.png");
        resourceManager->loadTexture("red_building_tower_right", "resources/buildings/red_tower_right.png");
        resourceManager->loadTexture("red_building_tower_down", "resources/buildings/red_tower_down.png");

        resourceManager->loadTexture("red_building_barrack_up", "resources/buildings/red_barrack_up.png");
        resourceManager->loadTexture("red_building_barrack_right", "resources/buildings/red_barrack_right.png");
        resourceManager->loadTexture("red_building_barrack_down", "resources/buildings/red_barrack_down.png");

        resourceManager->loadTexture("blu_building_base_up", "resources/buildings/blu_base_up.png");
        resourceManager->loadTexture("blu_building_base_right", "resources/buildings/blu_base_right.png");
        resourceManager->loadTexture("blu_building_base_down", "resources/buildings/blu_base_down.png");

        resourceManager->loadTexture("blu_building_tower_up", "resources/buildings/blu_tower_up.png");
        resourceManager->loadTexture("blu_building_tower_right", "resources/buildings/blu_tower_right.png");
        resourceManager->loadTexture("blu_building_tower_down", "resources/buildings/blu_tower_down.png");

        resourceManager->loadTexture("blu_building_barrack_up", "resources/buildings/blu_barrack_up.png");
        resourceManager->loadTexture("blu_building_barrack_right", "resources/buildings/blu_barrack_right.png");
        resourceManager->loadTexture("blu_building_barrack_down", "resources/buildings/blu_barrack_down.png");

        //// OBJECTS
        resourceManager->loadTexture("object_barrel", "resources/other_objects/barrel.png");
        resourceManager->loadTexture("object_rock", "resources/other_objects/rock.png");
        resourceManager->loadTexture("object_tree", "resources/other_objects/woods.png");
        resourceManager->loadTexture("object_healing_poition", "resources/other_objects/health_poition.png");
        resourceManager->loadTexture("object_stamina_poition", "resources/other_objects/stamina_poition.png");
        resourceManager->loadTexture("object_strength_poition", "resources/other_objects/strength_poition.png");
    }


    void initInterface()
    {
        if(interfaceManager == nullptr) return;
        if(resourceManager ==  nullptr) return;

        ////MAIN
        interfaceManager->addInterface("main",
                                       "resources/interface_config/main_interface.cfg",
                                       *resourceManager);

        ////UNITS
        interfaceManager->addInterface("unit_knight",
                                       "resources/interface_config/knight_interface.cfg",
                                       *resourceManager);
        interfaceManager->addInterface("unit_troll",
                                       "resources/interface_config/troll_interface.cfg",
                                       *resourceManager);
        interfaceManager->addInterface("unit_archer",
                                       "resources/interface_config/archer_interface.cfg",
                                       *resourceManager);
        interfaceManager->addInterface("unit_atrons",
                                       "resources/interface_config/atrons_interface.cfg",
                                       *resourceManager);
        interfaceManager->addInterface("unit_berserk",
                                       "resources/interface_config/berserk_interface.cfg",
                                       *resourceManager);
        interfaceManager->addInterface("unit_wizard",
                                       "resources/interface_config/wizard_interface.cfg",
                                       *resourceManager);
        interfaceManager->addInterface("unit_worker",
                                       "resources/interface_config/worker_interface.cfg",
                                       *resourceManager);

        ////BUILDINGS
        interfaceManager->addInterface("building_base",
                                       "resources/interface_config/base_interface.cfg",
                                       *resourceManager);
        interfaceManager->addInterface("building_tower",
                                       "resources/interface_config/battle_building_interface.cfg",
                                       *resourceManager);
        interfaceManager->addInterface("building_barrack",
                                       "resources/interface_config/battle_building_interface.cfg",
                                       *resourceManager);

        //// OBJECTS
        interfaceManager->addInterface("object_barrel",
                                       "resources/interface_config/barrel_interface.cfg",
                                       *resourceManager);
        interfaceManager->addInterface("object_rock",
                                       "resources/interface_config/rock_interface.cfg",
                                       *resourceManager);
        interfaceManager->addInterface("object_tree",
                                       "resources/interface_config/tree_interface.cfg",
                                       *resourceManager);
        interfaceManager->addInterface("object_healing_poition",
                                       "resources/interface_config/healing_poition_interface.cfg",
                                       *resourceManager);
        interfaceManager->addInterface("object_stamina_poition",
                                       "resources/interface_config/stamina_poition_interface.cfg",
                                       *resourceManager);
        interfaceManager->addInterface("object_strength_poition",
                                       "resources/interface_config/strength_poition_interface.cfg",
                                       *resourceManager);
    }


    void drawInterface()
    {
        if(!currentInterface.empty())
            interfaceManager->getInterface(currentInterface).draw(window);

        // draw next turn button
        sf::Sprite next_turn_button;
        auto m_pos = sf::Mouse::getPosition(window);

        if (unsigned(m_pos.x) < window.getSize().x && unsigned(m_pos.x) > window.getSize().x - 81 &&
            unsigned(m_pos.y) < 81 && unsigned(m_pos.y) > 0)
        {
            mouse_on_turn = 1;
            next_turn_button.setTexture(resourceManager->getTexture("darker_turn_button"));
        } else {
            mouse_on_turn = 0;
            next_turn_button.setTexture(resourceManager->getTexture("turn_button"));
        }

        if(mouse_on_turn && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            next_turn_button.setTexture(resourceManager->getTexture("pressed_turn_button"));
        }

        next_turn_button.setPosition(window.getSize().x - 81, 0);
        window.draw(next_turn_button);


        // draw score table
        sf::Sprite score_table(resourceManager->getTexture("scores"));
        score_table.setPosition(window.getSize().x - 180, window.getSize().y - 80);

        window.draw(score_table);

        sf::RectangleShape current_player_marker(sf::Vector2f(50, 25));
        current_player_marker.setOutlineThickness(3);
        current_player_marker.setOutlineColor(sf::Color(0xFF, 0xC1, 0x07, 0xFF));
        current_player_marker.setFillColor(sf::Color(0, 0, 0, 0));

        if(turn == Team::Red){
            current_player_marker.setPosition(score_table.getPosition() + sf::Vector2f(14, 8));
        } else {
            current_player_marker.setPosition(score_table.getPosition() + sf::Vector2f(14, 44));
        }

        window.draw(current_player_marker);


        // draw current scores
        sf::Font font;
        font.loadFromFile("arial.ttf");

        // red score
        sf::Text score(std::to_string(red_points), font, 23);
        score.setOutlineThickness(1);
        score.setOutlineColor(sf::Color::Black);
        score.setFillColor(sf::Color(0xE0, 0xE0, 0xE0, 0xFF));

        score.setPosition(score_table.getPosition() + sf::Vector2f(70, 6));
        window.draw(score);

        // blu score
        score.setString(std::to_string(blu_points));
        score.setPosition(score_table.getPosition() + sf::Vector2f(70, 42));
        window.draw(score);

        splasher->draw(window);

        if(info)
            info->draw(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

    }


    void selectCell()
    {
        auto mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        int cell_x_pos = int(floor(float(mouse_pos.x)/CELL_SELECTOR_SIZE));
        int cell_y_pos = int(floor(float(mouse_pos.y)/CELL_SELECTOR_SIZE));

        if(cell_x_pos < 0){
            sf::RectangleShape line(sf::Vector2f(2, field->getSize().y*CELL_SELECTOR_SIZE));
            line.setFillColor(sf::Color::Red);
            line.setPosition(0,0);
            window.draw(line);
        }
        if(cell_y_pos < 0){
            sf::RectangleShape line(sf::Vector2f(field->getSize().x*CELL_SELECTOR_SIZE, 2));
            line.setFillColor(sf::Color::Red);
            line.setPosition(0,0);
            window.draw(line);
        }
        if(cell_x_pos >= field->getSize().x){
            sf::RectangleShape line(sf::Vector2f(2, field->getSize().y*CELL_SELECTOR_SIZE));
            line.setFillColor(sf::Color::Red);
            line.setOrigin(line.getSize().x, line.getSize().y);
            line.setPosition(field->getSize().x*CELL_SELECTOR_SIZE,
                             field->getSize().y*CELL_SELECTOR_SIZE);
            window.draw(line);
        }
        if(cell_y_pos >= field->getSize().y){
            sf::RectangleShape line(sf::Vector2f(field->getSize().x*CELL_SELECTOR_SIZE, 2));
            line.setFillColor(sf::Color::Red);
            line.setOrigin(line.getSize().x, line.getSize().y);
            line.setPosition(field->getSize().x*CELL_SELECTOR_SIZE,
                             field->getSize().y*CELL_SELECTOR_SIZE);
            window.draw(line);
        }

        if(cell_x_pos < 0 || cell_x_pos >= field->getSize().x ||
           cell_y_pos < 0 || cell_y_pos >= field->getSize().y)
        {
            return;
        }

        sf::RectangleShape selector(sf::Vector2f(CELL_SELECTOR_SIZE-2, CELL_SELECTOR_SIZE-2));
        selector.setPosition(cell_x_pos*CELL_SELECTOR_SIZE+1, cell_y_pos*CELL_SELECTOR_SIZE+1);

        selector.setOutlineThickness(1);
        selector.setOutlineColor(sf::Color::Black);
        selector.setFillColor(sf::Color(0,0,0,0));

        window.draw(selector);
    }


    void resizeEvent(unsigned uNewWidth, unsigned uNewHeight)
    {
        auto view = window.getView();
        view.setSize(uNewWidth, uNewHeight);
        view.zoom(0.5);
        window.setView(view);
    }


    void nextPlayer()
    {
        markedEntity.clear();
        markedObject.clear();

        if(turn == Team::Red){
            turn = Team::Blu;
        } else {
            turn = Team::Red;
        }

        if(nextStep){
            iTurnsLeft++;
            auto points = field->gameStep();

            game_finished = rules.checkWinner();
            winner = rules.getWinner();

            red_points += int(points.first * points_mod);
            blu_points += int(points.second * points_mod);

            splasher->splash(new GameInfoWindow(window, "next turn"));
        }

        nextStep = !nextStep;
    }

    void mousePressEvent(int button, int x, int y)
    {
        press_x = x;
        press_y = y;

        old_x = x;
        old_y = y;

        auto mouse_pos = window.mapPixelToCoords(sf::Vector2i(x, y));
        int cell_x_pos = int(floor(float(mouse_pos.x)/CELL_SELECTOR_SIZE));
        int cell_y_pos = int(floor(float(mouse_pos.y)/CELL_SELECTOR_SIZE));


        std::vector<std::string> pressed_buttons;

        if(button == sf::Mouse::Left || button == sf::Mouse::Right){
            // throw click into interface if it is

            if(button == sf::Mouse::Right)
                window.setMouseCursorVisible(0);

            if(!currentInterface.empty()){
                auto& interface = interfaceManager->getInterface(currentInterface);
                auto y_offset = window.getSize().y - interface.getSize().y;

                // handle interface tapping
                if(y > int(y_offset)){

                    std::string interface_button;
                    int press_flag = interface.click(x, y-y_offset, interface_button, 1);

                    if(button == sf::Mouse::Left){
                        switch(press_flag){
                        case 1:     // button pressed
                            handlePressInterface(interface_button);
                            break;
                        case -1:    // button released
                            handleReleaseInterface(interface_button);
                            break;
                        default: break;
                        }
                    } else {
                        interface.click(x, y-y_offset, interface_button, 1);
                        if(press_flag){
                            std::string info_str;
                            try {
                                auto& b = interfaceManager->getInterface(currentInterface).getButton(interface_button);
                                info_str = b.getName();
                            } catch (std::out_of_range e) {
                                std::cout << "Warning! " << e.what() << std::endl;
                                return;
                            }

                            info = new GameInfoWindow(window, info_str);
                        }
                        else
                            info = new GameInfoWindow(window,
                            interfaceManager->getInterface(currentInterface).getName()+ "\ninterface");
                    }
                }

                // handle field tapping
                else
                {
                    if(cell_x_pos < 0 || cell_x_pos >= field->getSize().x ||
                       cell_y_pos < 0 || cell_y_pos >= field->getSize().y)
                    {
                        return;
                    }

                    auto entity_under_cursor = field->getEntity(cell_x_pos, cell_y_pos);

                    if(button == sf::Mouse::Left){
                        if(markedEntity == entity_under_cursor && markedObject.empty()
                        && !entity_under_cursor.empty() && entity_under_cursor.getTeam() == turn){
                            markedEntity = EntityInterface(nullptr);
                            return;
                        }
                        pressed_buttons = interface.getPressedButtons();
                        handlePressCell(button, pressed_buttons, cell_x_pos, cell_y_pos);
                    } else {
                        if(!entity_under_cursor.empty())
                            info = new GameInfoWindow(window, entity_under_cursor.getInfo());
                    }
                }
            } else {
                // press on entity
                // check current player color and unit color

                if(cell_x_pos < 0 || cell_x_pos >= field->getSize().x ||
                   cell_y_pos < 0 || cell_y_pos >= field->getSize().y)
                {
                    return;
                }

                auto entity_under_cursor = field->getEntity(cell_x_pos, cell_y_pos);

                if(button == sf::Mouse::Left){
                    if(!entity_under_cursor.empty() && entity_under_cursor.getTeam() == turn){
                        if(entity_under_cursor.getEntityType() == Entity::Object)
                            return;

                        markedEntity = entity_under_cursor;
                    }
                } else {
                    if(!entity_under_cursor.empty())
                        info = new GameInfoWindow(window, entity_under_cursor.getInfo());
                }
            }
        }
    }


    void mouseMoveEvent(int new_x, int new_y)
    {
        int dx = new_x - old_x;
        int dy = new_y - old_y;

        // move camera
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){

            auto view = window.getView();
            view.move(-dx/2.f, -dy/2.f);
            window.setView(view);
        }

        old_x = new_x;
        old_y = new_y;
    }


    void mouseReleaseEvent(int button, int x, int y)
    {
        old_x = x;
        old_y = y;

        if(button == sf::Mouse::Right){
            window.setMouseCursorVisible(1);
            delete info;
            info = nullptr;
        }

        if(button == sf::Mouse::Left && mouse_on_turn)
            nextPlayer();
    }


    void keyPressedEvent(int button)
    {
        if(button == sf::Keyboard::Escape){
            markedEntity.clear();
            markedObject.clear();
        }
    }


    void handlePressInterface(const std::string& button)
    {
        draw_ways = 0;
        draw_targets = 0;

        int points = (turn == Team::Red)?red_points:blu_points;

        //// Create units
        if(button == "create_worker"){
            if(points >= 1){
                try{
                    auto cmd = new CmdCreateUnit(markedEntity, field, Unit::Worker);
                    cmd_list->push(cmd);
                }
                catch(Command::empty_interface e){
                    std::cout << e.what() << std::endl;
                }
                catch(Entity::wrong_type e){
                    std::cout << e.what() << std::endl;
                }
            } else {
                splasher->splash(new GameInfoWindow(window, "you don't have enought score"));
            }
        }

        if(button == "create_melee"){
            if(points >= 2){
                try{
                    auto cmd = new CmdCreateUnit(markedEntity, field, Unit::Melee);
                    cmd_list->push(cmd);
                }
                catch(Command::empty_interface e){
                    std::cout << e.what() << std::endl;
                }
                catch(Entity::wrong_type e){
                    std::cout << e.what() << std::endl;
                }
            } else {
                splasher->splash(new GameInfoWindow(window, "you don't have enought score"));
            }
        }

        if(button == "create_range"){
            if(points >= 4){
                try{
                    auto cmd = new CmdCreateUnit(markedEntity, field, Unit::Range);
                    cmd_list->push(cmd);
                }
                catch(Command::empty_interface e){
                    std::cout << e.what() << std::endl;
                }
                catch(Entity::wrong_type e){
                    std::cout << e.what() << std::endl;
                }
            } else {
                splasher->splash(new GameInfoWindow(window, "you don't have enought score"));
            }
        }

        if(button == "create_nuker"){
            if(points >= 6){
                try{
                    auto cmd = new CmdCreateUnit(markedEntity, field, Unit::Nuker);
                    cmd_list->push(cmd);
                }
                catch(Command::empty_interface e){
                    std::cout << e.what() << std::endl;
                }
                catch(Entity::wrong_type e){
                    std::cout << e.what() << std::endl;
                }
            } else {
                splasher->splash(new GameInfoWindow(window, "you don't have enought score"));
            }
        }

        //// Spot interactive cells
        if(button == "move"){
            draw_ways = 1;
            markedEntity.calculateWays();
        }

        if(button == "attack" || button == "work"){
            draw_targets = 1;
            markedEntity.calculateTargets();
        }

        if(button == "build_tower")
        {

            if(points < 10)
            {
                interfaceManager->getInterface(currentInterface).reset();
                splasher->splash(new GameInfoWindow(window, "you don't have enought score"));
            }
        }

        if(button == "build_barrack")
        {
            if(points < 5)
            {
                interfaceManager->getInterface(currentInterface).reset();
                splasher->splash(new GameInfoWindow(window, "you don't have enought score"));
            }
        }

        //// Items interractions
        if(button == "destroy"){
            auto cmd = new CmdDestroyObject(field, markedEntity, markedObject);
            markedObject.clear();
            cmd_list->push(cmd);
        }

        if(button == "use"){
            auto cmd = new CmdUseItem(field, markedEntity, markedObject);
            markedObject.clear();
            cmd_list->push(cmd);
        }
    }


    void handleReleaseInterface(const std::string& button)
    {
        if(button == "move"){
            draw_ways = 0;
        }

        if(button == "attack" || button == "work"){
            draw_targets = 0;
        }
    }


    void handlePressCell(int mouse_button, const std::vector<std::string>& interface_buttons, int x, int y)
    {
        if(mouse_button == sf::Mouse::Left){
            for(auto b: interface_buttons){
                if(b == "create_red_base"){
                    interfaceManager->getInterface(currentInterface).reset();
                    auto cmd = new CmdBuild(Team::Red, field, x, y, Building::Type::Base, Building::Rot::Down);
                    cmd_list->push(cmd);
                }

                if(b == "create_blu_base"){
                    interfaceManager->getInterface(currentInterface).reset();
                    auto cmd = new CmdBuild(Team::Blu, field, x, y, Building::Type::Base, Building::Rot::Down);
                    cmd_list->push(cmd);
                }

                // building structures
                if(b == "build_tower"){
                    interfaceManager->getInterface(currentInterface).reset();
                    auto offset = markedEntity.getPos() - sf::Vector2i(x, y);

                    if(abs(offset.x) + abs(offset.y) == 1){
                        Building::Rot rot;
                        if(offset == sf::Vector2i(0, -1))
                            rot = Building::Rot::Up;
                        if(offset == sf::Vector2i(1, 0))
                            rot = Building::Rot::Right;
                        if(offset == sf::Vector2i(0, 1))
                            rot = Building::Rot::Down;
                        if(offset == sf::Vector2i(-1, 0))
                            rot = Building::Rot::Left;

                        auto cmd = new CmdBuild(markedEntity.getTeam(), field, x, y, Building::Type::Tower, rot);
                        cmd_list->push(cmd);
                    }
                }

                if(b == "build_barrack"){
                    interfaceManager->getInterface(currentInterface).reset();
                    auto offset = markedEntity.getPos() - sf::Vector2i(x, y);

                    if(abs(offset.x) + abs(offset.y) == 1){
                        Building::Rot rot;
                        if(offset == sf::Vector2i(0, -1))
                            rot = Building::Rot::Up;
                        if(offset == sf::Vector2i(1, 0))
                            rot = Building::Rot::Right;
                        if(offset == sf::Vector2i(0, 1))
                            rot = Building::Rot::Down;
                        if(offset == sf::Vector2i(-1, 0))
                            rot = Building::Rot::Left;

                        auto cmd = new CmdBuild(markedEntity.getTeam(), field, x, y, Building::Type::Barrack, Building::Rot::Down);
                        cmd_list->push(cmd);
                    }
                }

                // unit control
                if(b == "move"){
                    auto cmd = new CmdMove(field, markedEntity, x, y);
                    if(cmd->valid_p()){
                        draw_ways = 0;
                        interfaceManager->getInterface(currentInterface).reset();
                    }
                    cmd_list->push(cmd);
                }

                if(b == "attack"){
                    auto cmd = new CmdAttack(field, markedEntity, x, y);
                    if(cmd->valid_p()){
                        draw_targets = 0;
                        interfaceManager->getInterface(currentInterface).reset();
                    }
                    cmd_list->push(cmd);
                }

                if(b == "work"){
                    auto cmd = new CmdWork(field, markedEntity, x, y);

                    if(cmd->valid_p()){
                        draw_targets = 0;
                        interfaceManager->getInterface(currentInterface).reset();
                    }

                    cmd_list->push(cmd);
                }

                if(b == "take")
                {
                    auto delta = sf::Vector2i(x, y) - markedEntity.getPos();
                    if(abs(delta.x) + abs(delta.y) == 1){
                        interfaceManager->getInterface(currentInterface).reset();
                        markedObject = field->getEntity(x, y);
                        if(markedObject.getEntityType() != Entity::Object){
                            markedObject.clear();
                        }
                    }
                }
            }
        }
    }


    void handleReleaseCell(int mouse_button, const std::vector<std::string>& interface_buttons, int x, int y)
    {}
};

#endif // GAME_H



#endif // TGAME_H
