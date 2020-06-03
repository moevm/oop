#ifndef GameRoomMemento_hpp
#define GameRoomMemento_hpp
#include <filesystem>
#include <fstream>


#include "../simplifiedConverter/SimplifiedConverter.hpp"
#include "../gameRoom/GameRoom.hpp"


class GameRoomMemento : SimplifiedConverter
{
private:
    std::ifstream ifile;

    GameRoom<Rule> *gameRoom;

public:
    
    GameRoomMemento(std::string filename, GameRoom<Rule> *gameRoom);
    ~GameRoomMemento();

    
    void restoreMemento();
};
#endif /* GameRoomMemento_hpp */
