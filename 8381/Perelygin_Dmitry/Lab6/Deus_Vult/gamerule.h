#ifndef GAMERULE_H
#define GAMERULE_H

class GameRule
{
public:
    virtual ~GameRule() = default;
    virtual int get_UnitCount() = 0;
};

#endif // GAMERULE_H
