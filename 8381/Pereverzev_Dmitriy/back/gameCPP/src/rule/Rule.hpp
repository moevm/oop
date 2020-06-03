#ifndef Rule_hpp
#define Rule_hpp


#include <map>
#include "../player/Player.hpp"
#include "../TypeСonstants.hpp"

template <typename T>
class GameRoom;

class Rule
{
protected:
    
    double stepTime;

    
    

public:
    
    std::function<bool(Player *&, Player *&)> sequenceOfMoves;
    virtual unsigned int getType() = 0;
    double getStepTime();
    template <class T>
    bool checkWin(GameRoom<T> *gameRoom);
};
#endif /* Rule_hpp */
