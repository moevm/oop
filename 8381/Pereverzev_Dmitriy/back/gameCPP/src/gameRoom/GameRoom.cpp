#include "GameRoom.hpp"















template <class T>
GameRoom<T>::GameRoom(std::string editorID, std::string roomID, std::string roomName, unsigned int rowsQuantity, unsigned int columnsQuantity, UUID *uuidGen, NeutralObjectFactory *NeutralObjectFactory, CombatObjectTypeFactory *combatObjectTypeFactory, unsigned int rule)
{
    

    this->roomID = roomID;
    this->roomName = roomName;
    this->mediator = new FieldMediator;
    this->field = new Field(rowsQuantity, columnsQuantity, this->mediator);
    this->uuidGen = uuidGen;
    this->neutralObjectFactory = neutralObjectFactory;
    this->combatObjectTypeFactory = combatObjectTypeFactory;
    this->field->attachEvent("object updated", this);
    editor = new Editor(editorID, field, uuidGen, neutralObjectFactory);
    this->rule = new T();
    this->nowPlayer = nullptr;
    
}

template <>
GameRoom<Rule>::GameRoom(std::string editorID, std::string roomID, std::string roomName, unsigned int rowsQuantity, unsigned int columnsQuantity, UUID *uuidGen, NeutralObjectFactory *NeutralObjectFactory, CombatObjectTypeFactory *combatObjectTypeFactory, unsigned int rule)
{
    

    this->roomID = roomID;
    this->roomName = roomName;
    this->mediator = new FieldMediator;
    this->field = new Field(rowsQuantity, columnsQuantity, this->mediator);
    this->uuidGen = uuidGen;
    this->neutralObjectFactory = neutralObjectFactory;
    this->combatObjectTypeFactory = combatObjectTypeFactory;
    this->field->attachEvent("object updated", this);
    editor = new Editor(editorID, field, uuidGen, neutralObjectFactory);
    
    if (rule == 0)
        this->rule = new Rule1();
    if (rule == 1)
        this->rule = new Rule2();
    this->nowPlayer = nullptr;
    
    
}













template </* class T */>
GameRoom<Rule>::~GameRoom()
{
    delete this->field;

    delete this->uuidGen;
    delete this->neutralObjectFactory;
    delete this->combatObjectTypeFactory;
}


template </* class T */>
FieldCell *GameRoom<Rule>::getFieldCell(unsigned int x, unsigned int y)
{
    

    return &(this->field->getFieldCell(x, y));
}

template </* class T */>
unsigned int GameRoom<Rule>::getFieldRowsQuantity()
{
    return this->field->getRowsQuantity();
}

template </* class T */>
unsigned int GameRoom<Rule>::getFieldColumnsQuantity()
{
    return this->field->getColumnsQuantity();
}


























































template <typename T>
void GameRoom<T>::nextPlayer()
{
    

    
    

    std::vector<Player *>::iterator it = std::find(players.begin(), players.end(), nowPlayer);
    if (it != players.end())
    {
        unsigned int index = std::distance(players.begin(), it);
        if (index >= players.size() - 1)
            nowPlayer = players[0];
        else
            nowPlayer = players[index + 1];
    }
    {
        
        
        v8::Local<v8::Object> data = Nan::New<v8::Object>();

        
        
        

        
        SetObjProperty(data, "roomID", roomID);
        Nan::Set(data, Nan::New("roomID").ToLocalChecked(), Nan::New(roomID.c_str()).ToLocalChecked());

        SetObjProperty(data, "playerName", nowPlayer->getPlayerName());
        

        fireEvent("active player has changed", data);
    }
}

template </* class T */>
UUID *GameRoom<Rule>::getUuidGen() { return uuidGen; }

template </* class T */>
NeutralObjectFactory *GameRoom<Rule>::getNeutralObjectFactory() { return neutralObjectFactory; }

template </* class T */>
CombatObjectTypeFactory *GameRoom<Rule>::getCombatObjectTypeFactory() { return combatObjectTypeFactory; }

template </* class T */>
Mediator *GameRoom<Rule>::getMediator() { return mediator; }


template </* class T */>
Editor *GameRoom<Rule>::getEditor()
{
    
    return editor;
}

template </* class T */>
Player *GameRoom<Rule>::getPlayer(std::string playerID)
{
    if (players.size() > 0)
    {
        
        auto player = (std::find_if(players.begin(), players.end(), [playerID](Player *player) {
            return (player->getPlayerID() == playerID);
        }));
        
        if (player != players.end())
            return *player;
        
        
    }
    return nullptr;
}

template </* class T */>
unsigned int GameRoom<Rule>::getPlayersQuantity()
{
    return this->players.size();
}

template </* class T */>
std::string GameRoom<Rule>::getRoomID()
{
    return this->roomID;
}

template </* class T */>
std::string GameRoom<Rule>::getRoomName()
{
    return this->roomName;
}

template </* class T */>
std::vector<std::string> GameRoom<Rule>::getPlayersID()
{
    std::vector<std::string> response;
    for (auto const &elem : this->players)
        response.push_back(elem->getPlayerID());
    return response;
}

template </* class T */>
std::vector<std::string> GameRoom<Rule>::getPlayersNames()
{
    std::vector<std::string> response;
    std::for_each(this->players.begin(), this->players.end(), [&response](Player *player) { response.push_back(player->getPlayerName()); });
    return response;
}

template </* class T */>
void GameRoom<Rule>::addPlayer(std::string playerID, std::string PlayerName)
{
    
    if (getPlayer(playerID) != nullptr)
        return;
    Player *player = new Player(playerID, PlayerName, field, uuidGen, combatObjectTypeFactory);

    if (nowPlayer == nullptr)
    {
        

        nowPlayer = player;
        nextPlayer();
        
    }
    

    player->attachEvent("log", this);

    this->players.push_back(player);
    
    
    std::sort(players.begin(), players.end(), rule->sequenceOfMoves);
    

    
    fireEvent("tabel of GameRooms update");

    
    
    
    
    
    
    
    
}

template </* class T */>
void GameRoom<Rule>::removePlayer(std::string playerID)
{
    
    

    this->players.erase((std::remove_if(this->players.begin(), this->players.end(), [playerID](Player *player) {
                            
                            return (player->getPlayerID() == playerID ? true : false);
                        })),
                        this->players.end());
    
}









template </* class T */>
v8::Local<v8::Object> GameRoom<Rule>::getGameRoomFieldData()
{
    v8::Local<v8::Object> data = Nan::New<v8::Object>();
    SetObjProperty(data, "landscapes", field->getLandscapesData());
    SetObjProperty(data, "objects", field->getObjectsData());
    SetObjProperty(data, "rowsQuantity", getFieldRowsQuantity());
    SetObjProperty(data, "columnsQuantity", getFieldColumnsQuantity());
    fireEvent("get full room", data);
    return data;
}


template <>
v8::Local<v8::Object> GameRoom<Rule>::getGameRoomData()
{
    
    v8::Local<v8::Object> data = Nan::New<v8::Object>();
    SetObjProperty(data, "roomID", roomID);
    SetObjProperty(data, "roomName", roomName);
    SetObjProperty(data, "players", static_cast<unsigned int>(players.size()));
    SetObjProperty(data, "fieldSize", std::to_string(getFieldRowsQuantity()) + " * " + std::to_string(getFieldColumnsQuantity()));
    return data;
}

template </* class T */>
void GameRoom<Rule>::eventHandler(Event *event)
{
    if (event->getSEventId() == "object updated")
    {
        v8::Local<v8::Object> data = Nan::New<v8::Object>();
        SetObjProperty(data, "objectInfo", event->getData());
        SetObjProperty(data, "roomID", getRoomID());

        fireEvent("object updated", data);
    }
};

template </* class T */>
v8::Local<v8::Object> GameRoom<Rule>::getFullInfo()
{
    v8::Local<v8::Object> info = Nan::New<v8::Object>();
    v8::Local<v8::Array> playersInfo = Nan::New<v8::Array>();
    

    SetObjProperty(info, "nowPlayer", static_cast<unsigned int>(std::distance(players.begin(), std::find(players.begin(), players.end(), nowPlayer))));
    SetObjProperty(info, "rule", rule->getType());
    

    SetObjProperty(info, "field", field->getFullInfo());
    

    
    

    std::for_each(players.begin(), players.end(), [this, &playersInfo](Player *player) { SetArrProperty(playersInfo, playersInfo->Length(), player->getFullInfo()); });
    

    SetObjProperty(info, "playersInfo", playersInfo);
    

    return info;
}