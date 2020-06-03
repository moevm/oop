#ifndef Rule2_hpp
#define Rule2_hpp

#include "../Rule.hpp"
#define NEED_UNITS 20

class Rule2 : public Rule
{
public:
    
    Rule2();
    
    unsigned int getType() override;
    template <class T>
    bool checkWin(GameRoom<T> *gameRoom);
};
#endif /* Rule2_hpp */
