#include "Game.hpp"
Game::Game()
{
    this->uuidGen = new UUID;
    this->neutralObjectFactory = new NeutralObjectFactory;
    this->combatObjectTypeFactory = new CombatObjectTypeFactory;
}
Game::~Game()
{
    this->gameRooms.clear();
    delete this->uuidGen;
    delete this->neutralObjectFactory;
    delete this->combatObjectTypeFactory;
}

Game *Game::p_game;

Game *Game::getInstance()
{
    if (p_game == nullptr)
        p_game = new Game();
    return p_game;
}

void Game::addGameRoom(std::string editorID, std::string roomID, std::string roomName, unsigned int rowsQuantity, unsigned int columnsQuantity, unsigned int rule)
{

    GameRoom<Rule> *room = new GameRoom<Rule>(editorID, roomID, roomName, rowsQuantity, columnsQuantity, uuidGen, neutralObjectFactory, combatObjectTypeFactory, rule);

    gameRooms.push_back(room);

    room->attachEvent("object updated", this);
    room->attachEvent("tabel of GameRooms update", this);
    room->attachEvent("get full room", this);
    room->attachEvent("winner found", this);

    fireEvent("tabel of GameRooms update", getGameRoomsInfo());
}

std::string Game::removeGameRoom(std::string roomID)
{
    std::remove_if(this->gameRooms.begin(), this->gameRooms.end(), [roomID](GameRoom<Rule> *room) {
        return ((room->getRoomID() == roomID) ? true : false);
    });
    return "removed";
}

GameRoom<Rule> *Game::getGameRoom(std::string roomID)
{
    std::__1::__wrap_iter<GameRoom<Rule> **> response = std::find_if(gameRooms.begin(), gameRooms.end(), [roomID](GameRoom<Rule> *room) {
        return (room->getRoomID() == roomID);
    });
    if (response == gameRooms.end())
        return nullptr;
    return *response;
}

std::string Game::executeСommand(std::string playerID, std::string command)
{

    return (std::string("") + "Command comleted: " + "\n\tFor player: " + playerID + "\n\tCommand: " + command);
}

v8::Local<v8::Object> Game::getGameRoomsInfo()
{
    v8::Local<v8::Object> data = Nan::New<v8::Object>();
    unsigned int index = 0;
    std::for_each(gameRooms.begin(), gameRooms.end(), [&data, &index, this](GameRoom<Rule> *gameRoom) {
        SetObjProperty(data, index++, gameRoom->getGameRoomData());
    });

    return data;
}

void Game::eventHandler(Event *event)
{

    if (event->getSEventId() == "object updated")
    {
        fireEvent("object updated", event->getData());
    }
    else if (event->getSEventId() == "tabel of GameRooms update")
    {
        fireEvent("tabel of GameRooms update", getGameRoomsInfo());
    }
    else if (event->getSEventId() == "get full room")
    {
        fireEvent("get full room", event->getData());
    }
};

void Game::saveRoom(std::string editorID, std::string roomID)
{

    GameRoom<Rule> *gameRoom = getGameRoom(roomID);
    if (gameRoom->getEditor())
        historyGameRooms[roomID].push_back(new GameRoomMemento(std::string(roomID + "#" + std::to_string(historyGameRooms[roomID].size())), gameRoom));
}
void Game::loadRoom(std::string editorID, std::string roomID, unsigned int saveID)
{
    GameRoom<Rule> *gameRoom = getGameRoom(roomID);
    if (gameRoom->getEditor())
    {

        historyGameRooms[roomID][saveID]->restoreMemento();
    }
}