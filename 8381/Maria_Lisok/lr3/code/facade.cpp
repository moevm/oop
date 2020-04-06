#include "facade.h"


Facade::Facade(Ui::MainWindow *ui, Game *game): ui(ui), game(game)
{}

void Facade::getGameInfo()
{
   GameCommand com(game, GAME_INFO, map<string, Data>());
   map<string, int> answers = com.mainInfoAboutObj();
   string output{};
   for(auto it = answers.begin(); it != answers.end(); ++it) {
         output+=it->first + to_string(it->second)+"\n";
   }
}

void Facade::getBaseInfo(int number)
{
    map<string, Data> params;
    Data data;
    data.x = number;
    params["base num"] = data;
    GameCommand com(game, BASE_INFO, params);
    map<string, int> answers = com.mainInfoAboutObj();
    string output{};
    for(auto it = answers.begin(); it != answers.end(); ++it) {
          output+=it->first + to_string(it->second)+"\n";
    }
}

void Facade::getUnitInfo(int x, int y)
{
    map<string, Data> params;
    Data data;
    data.x = x;
    data.y = y;
    params["infoParams"] = data;
    GameCommand com(game, UNIT_INFO, params);
    map<string, int> answers = com.mainInfoAboutObj();
    string output{};
    for(auto it = answers.begin(); it != answers.end(); ++it) {
          output+=it->first + to_string(it->second)+"\n";
    }
}

void Facade::getNeutralInfo(int x, int y)
{
    map<string, Data> params;
    Data data;
    data.x = x;
    data.y = y;
    params["infoParams"] = data;
    GameCommand com(game, NEUTRAL_INFO, params);
    map<string, int> answers = com.mainInfoAboutObj();
    string output{};
    for(auto it = answers.begin(); it != answers.end(); ++it) {
          output+=it->first + to_string(it->second)+"\n";
    }
}

void Facade::getLandscapeInfo(int x, int y)
{
    map<string, Data> params;
    Data data;
    data.x = x;
    data.y = y;
    params["infoParams"] = data;
    GameCommand com(game, LAND_CELL, params);
    map<string, int> answers = com.mainInfoAboutObj();
    string output{};
    for(auto it = answers.begin(); it != answers.end(); ++it) {
          output+=it->first + to_string(it->second)+"\n";
    }
}

void Facade::moveUnit(int x, int y, int xDelta, int yDelta)
{
    map<string, Data> params;
    Data data;
    data.x = x;
    data.y = y;
    params["pos"] = data;
    Data dataMove;
    data.x = xDelta;
    data.y = yDelta;
    params["move"] = dataMove;
    GameCommand com(game, MOVE, params);
    map<string, int> answers = com.mainInfoAboutObj();
    string output{};
    for(auto it = answers.begin(); it != answers.end(); ++it) {
          output+=it->first + to_string(it->second)+"\n";
    }
}

void Facade::attackUnit(int x, int y, int xDelta, int yDelta)
{
    map<string, Data> params;
    Data data;
    data.x = x;
    data.y = y;
    params["pos"] = data;
    Data dataAttack;
    data.x = xDelta;
    data.y = yDelta;
    params["attack pos"] = dataAttack;
    GameCommand com(game, ATTACK, params);
    map<string, int> answers = com.mainInfoAboutObj();
    string output{};
    for(auto it = answers.begin(); it != answers.end(); ++it) {
          output+=it->first + to_string(it->second)+"\n";
    }
}

void Facade::addBase(int x, int y, int maxUnitsCount, int health)
{
    int baseNum = game->getBases().size();
    map<string, Data> params;
    Data data;
    data.x = baseNum;
    params["base num"] = data;
    Data dataPos;
    dataPos.x = x;
    dataPos.y = y;
    params["pos"] = dataPos;
    Data addParams;
    dataPos.x = maxUnitsCount;
    dataPos.y = health;
    params["addParams"] = addParams;
    GameCommand com(game, BASE_ADD, params);
    map<string, int> answers = com.mainInfoAboutObj();
    string output{};
    for(auto it = answers.begin(); it != answers.end(); ++it) {
          output+=it->first + to_string(it->second)+"\n";
    }
}

void Facade::addUnit(int x, int y, int base, int type)
{
    map<string, Data> params;
    Data data ={base,0};
    data.x = x;
    data.y = y;
    params["base num"] = data;
    Data dataPos;
    dataPos.x = x;
    dataPos.y = y;
    params["addParams"] = dataPos;
    GameCommand com(game, UNIT_ADD, params);
    map<string, int> answers = com.mainInfoAboutObj();
    string output{};
    for(auto it = answers.begin(); it != answers.end(); ++it) {
          output+=it->first + to_string(it->second)+"\n";
    }
}

void Facade::addNeutral(int x, int y, int type)
{
      map<string, Data> params;
      Data data;
      data.x = x;
      data.y = y;
      params["addParams"] = data;
      GameCommand com(game, NEUTRAL_ADD, params);
      map<string, int> answers = com.mainInfoAboutObj();
      string output{};
      for(auto it = answers.begin(); it != answers.end(); ++it) {
            output+=it->first + to_string(it->second)+"\n";
      }
}

