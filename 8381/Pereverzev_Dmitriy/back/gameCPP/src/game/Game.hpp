#ifndef Game_hpp
#define Game_hpp

#include <string>
#include <map>

#include "../gameRoom/GameRoom.hpp"
#include "../field/Field.hpp"
#include "../uuid/UUID.hpp"
#include "../objects/neutralObject/NeutralObjectFactory.hpp"
#include "../player/Player.hpp"
#include "../eventProvider/EventProvider.hpp"
#include "../memento/GameRoomMemento.hpp"
#include "../rule/rule1/Rule1.hpp"
#include "../rule/rule2/Rule2.hpp"

class Game : public EventProvider
{
private:
    std::vector<GameRoom<Rule> *> gameRooms;
    std::map<std::string, std::vector<GameRoomMemento *>> historyGameRooms;

    UUID *uuidGen;
    NeutralObjectFactory *neutralObjectFactory;
    CombatObjectTypeFactory *combatObjectTypeFactory;
    

    Game();
    Game(const Game &);
    Game &operator=(Game &);
    ~Game();
    static Game *p_game;

public:
    static Game *getInstance();

    void addGameRoom(std::string editorID, std::string roomID, std::string roomName, unsigned int rowsQuantity, unsigned int columnsQuantity, unsigned int rule);
    std::string removeGameRoom(std::string roomID);

    GameRoom<Rule> *getGameRoom(std::string roomID);

    
    
    
    
    
    

    
    
    
    
    
    
    
    

    
    std::vector<std::string> getGameRoomPlayersIDList(std::string roomID); 
    
    

    std::string executeСommand(std::string playerID, std::string command);

    /* for room  */
    
    
    
    
    /*  */

    v8::Local<v8::Object> getGameRoomsInfo();
    void eventHandler(Event *event) override;

    void saveRoom(std::string editorID, std::string roomID);
    void loadRoom(std::string editorID, std::string roomID, unsigned int saveID);
};

#endif /* Game_hpp */
