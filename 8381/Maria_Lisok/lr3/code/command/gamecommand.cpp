#include "gamecommand.h"



map<string, int> GameCommand::baseInfo()
{
    map<string, int> information;
    int baseNum = params.find("base num")->second.x;
    if(baseNum > 0){
        if(static_cast<unsigned>(baseNum) < game->getBases().size()){
            BaseCommand com(game->getBaseByNum(baseNum),action, params);
            return com.mainInfoAboutObj();
        }else{
            information["not base with such number"] = baseNum;
        }
    }else{
        information["base number must be > 0"] = 0;
    }
    return information;
}

map<string, int> GameCommand::gameInfo()
{
    map<string, int> information;
    information["field height"] = static_cast<int>(game->getField()->getHeight());
    information["field width"] = static_cast<int>(game->getField()->getWidth());
    information["field max items"] = static_cast<int>(game->getField()->getMaxItems());
    information["count items on field"] = static_cast<int>(game->getField()->getCountOfItems());
    information["count of bases"] = static_cast<int>(game->getBases().size());
    return information;
}

map<string, int> GameCommand::attack()
{
    map<string, int> information;
    FieldCommand com(game->getField(), action, params);
    Unit* u = com.findItem();
    if(!u){
        information["no such unit"] = 0;
        return information;
    }
    for (Unit* i : game->getUnits())
    {
        if (i == u)
        {
            i->attack(params.find("attack pos")->second.x, params.find("attack pos")->second.y);
            information["attack was"] = 0;
            return information;
        }
    }
    information["not such attacker"] = -1;
    return information;
}

map<string, int> GameCommand::move()
{
    FieldCommand com(game->getField(), action, params);
    return com.mainInfoAboutObj();
}

map<string, int> GameCommand::addBase()
{
    int maxUnitsCount = params.find("addParams")->second.x;
    int health = params.find("addParams")->second.y;
    int x = params.find("pos")->second.x;
    int y = params.find("pos")->second.y;
    int baseNumb = params.find("base num")->second.x;
    game->createBase(maxUnitsCount, health, x, y, baseNumb);
    map<string, int> information;
    information["base was created"] = baseNumb;
    return information;
}

map<string, int> GameCommand::addNeutral()
{
    unsigned x = static_cast<unsigned>(params.find("addParams")->second.x);
    unsigned y = static_cast<unsigned>(params.find("addParams")->second.y);
    game->createNeutral(static_cast<NeutralType>(params.find("type")->second.x), x, y);
    map<string, int> information;
    information["action"] = NEUTRAL_ADD;
    information["pos x "] = static_cast<int>(x);
    information["pos y "] = static_cast<int>(y);
    return information;
}

map<string, int> GameCommand::addUnit()
{
    int baseNum = params.find("base num")->second.x;
    BaseCommand com(game->getBaseByNum(baseNum),action, params);
    return com.mainInfoAboutObj();
}

map<string, int> GameCommand::noSuchAct()
{
    map<string, int> information;
    information["no such action"] = 0;
    return information;
}

GameCommand::GameCommand(Game *game, Actions act, map<string, Data> param)
{
    this->game = game;
    action = act;
    params = param;
}

map<string, int> GameCommand::mainInfoAboutObj()
{
    if(action == GAME_INFO){
        return gameInfo();
    }else if(action == BASE_INFO){
        return baseInfo();
    }else if(action == LAND_INFO || action == NEUTRALS_INFO || action == UNITS_INFO){
        FieldCommand com(game->getField(), action, params);
        return com.mainInfoAboutObj();
    }else if(action == LAND_CELL || action == NEUTRAL_INFO || action == UNIT_INFO){
        FieldCommand com(game->getField(), action, params);
        return com.mainInfoAboutObj();
    }else if(action == MOVE){
        return move();
    }else if(action == ATTACK){
        return attack();
    }else if(action == BASE_ADD){
        return addBase();
    }else if(action == UNIT_ADD){
        return addUnit();
    }else if(action == NEUTRAL_ADD){
        return addNeutral();
    }else{
        return noSuchAct();
    }
}
