#ifndef GOGOLEV_STRATEGY_GAME_RULE_HPP
#define GOGOLEV_STRATEGY_GAME_RULE_HPP

#include "stl.hpp"
#include "enums.hpp"
#include "loggers/logger.hpp"

class Tile;
class Unit;
class UI;

class GameRule {
public:
    class GameHandler {
    public:
        virtual void setSize(int sizeX, int sizeY) = 0;
        virtual void setTile(int x, int y, char tileId) = 0;
        virtual Unit* createUnit(string key) = 0;
        virtual Unit* findUnit(int id) = 0;
        virtual UI* getUI () = 0;
        virtual Logger& getLogger () = 0;
    };

public:
    virtual bool isGameEnded();
    virtual void onGameStart(GameHandler *gameHandler);
    virtual void onGameUpdate();
    void reset();
    int getMaxUnits();

    Unit* getCitadel(Team team);

private:
    GameHandler *gameHandler;

    const int sizeX = 30;
    const int sizeY = 10;
    const int maxUnits = 50;
    int redCitadelId;
    int blueCitadelId;
    int frameCount;

    void fillRect(int minX, int minY, int maxX, int maxY, char tileId);
    void plaseVillage(int x, int y);
    void plaseNeutral(int x, int y, string type);
    Unit* plaseFortress(int minX, int minY, int maxX, int maxY, Team team);
};


#endif //GOGOLEV_STRATEGY_GAME_RULE_HPP
