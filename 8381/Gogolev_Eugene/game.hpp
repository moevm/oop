#ifndef GOGOLEV_STRATEGY_GAME_HPP
#define GOGOLEV_STRATEGY_GAME_HPP

#include "loggers/logger_proxy.hpp"
#include "units/unit.hpp"
#include "tiles/tile.hpp"
#include "game_rule.hpp"
#include "ui.hpp"
#include "tiles/meadow.hpp"
#include "tiles/fortress.hpp"
#include "tiles/water.hpp"

class Game : public Unit::GameHandler, GameRule::GameHandler {
public:
    Game (GameRule* rule, UI* ui);
    ~Game ();
    bool onField (int x, int y) override;
    void setSize (int sizeX, int sizeY) override;
    int getSizeX () const override;
    int getSizeY () const override;
    Tile* getTile (int x, int y) override;
    void setTile(int x, int y, char id) override;
    void setLogger (Logger* logger);
    UI* getUI () override;
    void setUI (UI* ui);
    Logger& getLogger () override;
    Unit* createUnit (string key) override;
    const vector<Unit*>* findUnits (int x, int y, int radius) override;
    Unit* findUnit (int id) override;
    void setTarget(Team team, int x, int y);

    void update ();
    void save(ostream &os);
    void load(istream &is);


private:
    int nextId = 1;
    int sizeX = 0;
    int sizeY = 0;
    Tile** tileMap = nullptr;
    GameRule* gameRule = nullptr;
    Logger* logger = nullptr;
    UI* ui = nullptr;
    map<int, Unit*> unitMap;
    vector<Unit*> cash;

    Fortress fortress;
    Meadow meadow;
    Water water;

    int toIndex (int x, int y) const;
    Unit* registerUnit (Unit* unit);
    Unit* createUnitInstance (string key);
    Tile* getTile(char id);
    void setTile (int x, int y, Tile* tile);
};

#endif //GOGOLEV_STRATEGY_GAME_HPP
