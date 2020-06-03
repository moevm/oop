#ifndef Rule1_hpp
#define Rule1_hpp

#include "../Rule.hpp"
#define NEED_RES 100

class Rule1 : public Rule
{
public:
    
    Rule1();
    
    unsigned int getType() override;
    template <class T>
    bool checkWin(GameRoom<T> *gameRoom);
};
#endif /* Rule1_hpp */
