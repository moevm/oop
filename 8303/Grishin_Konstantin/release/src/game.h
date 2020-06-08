#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <fstream>

#include "game_elements/team.h"
#include "game_elements/interface/entity_interface.h"


/*
 * Need to create some class
 * which says me, what interface
 * should be drawn while some
 * entity marked
 * * * * * * * * * * * * * * * * */


#define CELL_SELECTOR_SIZE 64

namespace sf {
    class RenderWindow;
    class Event;
}

class Field;
class EntityInterface;
class ResourceManager;
class GameInterfaceManager;
class CommandsQueue;
class Level;

class GameInfoWindow;
class SplashMessages;

class Logger;

class Game
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

    //log data
    Logger *logger;
    std::ofstream ofs;

public:
    Game(sf::RenderWindow &window, const Level& lvl);
    ~Game();

    void draw();
    void frameStep(float ms_time);

    void handleEvent(sf::Event& event); // Affects game state
    void addPoints(Team team, int score);

    void save(const std::string& name) const;

private:
    void loadResources();
    void initInterface();

    void drawInterface();
    void selectCell();
    void resizeEvent(unsigned uNewWidth, unsigned uNewHeight);
    void nextPlayer();

    void mousePressEvent(int button, int x, int y);
    void mouseMoveEvent(int new_x, int new_y);
    void mouseReleaseEvent(int button, int x, int y);
    void keyPressedEvent(int button);

    void handlePressInterface(const std::string& button);
    void handleReleaseInterface(const std::string& button);

    void handlePressCell(int mouse_button, const std::vector<std::string>& interface_buttons, int x, int y);
    void handleReleaseCell(int mouse_button, const std::vector<std::string>& interface_buttons, int x, int y);
};

#endif // GAME_H
