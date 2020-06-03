#include "GameRoomMemento.hpp"






GameRoomMemento::GameRoomMemento(std::string filename, GameRoom<Rule> *gameRoom)
{
    this->gameRoom = gameRoom;
    std::string dir = "saves/" + gameRoom->getRoomName() + "#" + gameRoom->getRoomID();
    
    if (!std::__fs::filesystem::exists(dir))
        std::__fs::filesystem::create_directory(dir);

    
    {
        std::ofstream ofile;
        ofile.open(dir + "/" + filename + ".json");
        
        ofile << JSONStringified(gameRoom->getFullInfo());
        

        ofile.close();
    }
    this->ifile.open(dir + "/" + filename + ".json");
}

GameRoomMemento::~GameRoomMemento()
{
    ifile.close();
}










void GameRoomMemento::restoreMemento()
{
    
    std::string jsonStr;
    ifile >> jsonStr;
    

    v8::Local<v8::Object> info = JSONParse(jsonStr);
    
    
    
    
    
    
    
    
    

    v8::Local<v8::Object> fieldInfo;

    if (!GetObjProperty(info, "field", fieldInfo))
        return;

    v8::Local<v8::Array> landscapes;
    unsigned int rowsQuantity;
    unsigned int columnsQuantity;
    unsigned int maximumObjectsQuantity;
    

    if (!GetObjProperty(fieldInfo, "rowsQuantity", rowsQuantity))
        return;
    

    if (!GetObjProperty(fieldInfo, "columnsQuantity", columnsQuantity))
        return;
    

    if (!GetObjProperty(fieldInfo, "maximumObjectsQuantity", maximumObjectsQuantity))
        return;
    
    
    for (unsigned int row = 0; row < rowsQuantity; row++)
        for (unsigned int column = 0; column < columnsQuantity; column++)
        {
            
            

            FieldCell *cell = gameRoom->getFieldCell(row, column);
            unsigned int landscapeType = 0;
            
            
            cell->setLandscape(new LandscapeProxy(landscapeType));

            
            
            
            cell->setObject(nullptr);
            
            
            
        }
    
    

    v8::Local<v8::Array> playersInfo;
    if (!GetObjProperty(info, "playersInfo", playersInfo))
        return;
    

    std::for_each(gameRoom->players.begin(), gameRoom->players.end(), [](Player *player) { delete player; });
    gameRoom->players.clear();

    unsigned int len = playersInfo->Length();
    for (unsigned int index = 0; index < len; ++index)
    {
        v8::Local<v8::Object> player;
        if (!GetArrProperty(playersInfo, index, player))
            return;
        

        std::string playerID;
        std::string playerName;
        if (!GetObjProperty(player, "playerID", playerID))
            return;
        
        if (!GetObjProperty(player, "playerName", playerName))
            return;
        

        gameRoom->addPlayer(playerID, playerName);

        { 
            unsigned int row, column;
            v8::Local<v8::Object> base;
            /*  */ v8::Local<v8::Object> stats;
            /*  */ /*  */ double health;
            if (!GetObjProperty(player, "base", base))
                return;
            if (!GetObjProperty(base, "x", column))
                return;
            if (!GetObjProperty(base, "y", row))
                return;
            if (!GetObjProperty(base, "stats", stats))
                return;
            if (!GetObjProperty(stats, "health", health))
                return;

            
            
            
            
            gameRoom->getPlayer(playerID)->createBase(row, column);
            
            gameRoom->getPlayer(playerID)->getBase()->setHealth(health);
            
            
            
        }
        { 
            v8::Local<v8::Object> resourceBag;
            std::map<unsigned int, double> restoredResourceBag;
            
            
            

            if (!GetObjProperty(player, "resourceBag", resourceBag))
                return;
            

            if (!ObjToMap(resourceBag, restoredResourceBag))
                return;
            

            for (std::map<unsigned int, double>::iterator it = restoredResourceBag.begin(); it != restoredResourceBag.end(); ++it)
                gameRoom->getPlayer(playerID)->getResourceBag()->addResource(it->first, it->second);
        }
    }

    { 
        unsigned int nowPlayerIndex = 0;
        if (GetObjProperty(info, "nowPlayer", nowPlayerIndex))
            gameRoom->nowPlayer = gameRoom->players[nowPlayerIndex];
    }

    
    

    {
        v8::Local<v8::Array> units;
        if (!GetObjProperty(fieldInfo, "units", units))
            return;
        for (unsigned int index = 0; index < units->Length(); index++)
        {

            v8::Local<v8::Object> unit;
            /*  */ std::string playerID;
            /*  */ unsigned int objectType, row, column;
            /*  */ v8::Local<v8::Object> stats;
            /*  */ /*  */ double health;
            if (!GetArrProperty(units, index, unit))
                return;
            if (!GetObjProperty(unit, "playerID", playerID))
                return;
            if (!GetObjProperty(unit, "objectType", objectType))
                return;
            if (!GetObjProperty(unit, "y", row))
                return;
            if (!GetObjProperty(unit, "x", column))
                return;
            if (!GetObjProperty(unit, "stats", stats))
                return;
            if (!GetObjProperty(stats, "health", health))
                return;
            gameRoom->getPlayer(playerID)->createUnit(row, column, objectType);
            static_cast<Unit *>(gameRoom->getFieldCell(row, column)->getObject())->setHealth(health);
        }
    }

    
    { 
        v8::Local<v8::Array> resGens;
        

        if (!GetObjProperty(fieldInfo, "resGens", resGens))
            return;
        

        for (unsigned int index = 0; index < resGens->Length(); index++)
        {
            
            v8::Local<v8::Object> resGen;
            /*  */ std::string playerID;
            /*  */ unsigned int objectType, row, column;
            /*  */ v8::Local<v8::Object> stats;
            /*  */ /*  */ double coefficient;
            if (!GetArrProperty(resGens, index, resGen))
                return;
            if (!GetObjProperty(resGen, "playerID", playerID))
                return;
            if (!GetObjProperty(resGen, "objectType", objectType))
                return;
            if (!GetObjProperty(resGen, "y", row))
                return;
            if (!GetObjProperty(resGen, "x", column))
                return;
            if (!GetObjProperty(resGen, "stats", stats))
                return;
            if (!GetObjProperty(stats, "coefficient", coefficient))
                return;

            gameRoom->editor->createResourceGenerator(row, column, objectType);
            static_cast<ResourceGenerator *>(gameRoom->getFieldCell(row, column)->getObject())->setCoefficient(coefficient);
            static_cast<ResourceGenerator *>(gameRoom->getFieldCell(row, column)->getObject())->setPlayerID(playerID);
            
        }
    }

    
    
    
    
    
    
    
    

    
    
    
}