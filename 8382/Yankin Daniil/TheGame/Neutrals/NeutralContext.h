#pragma once

#include "Object/Object.h"
#include "NeutralObject.h"

class NeutralPlayer;


class NeutralContext : public Object
{
public:
    NeutralContext(Point point, NeutralPlayer* player);
    ~NeutralContext();

    uint8_t getGroupType() override;
    uint8_t getObjectType() override;
    Point getPoint() override;

    void setStrategy(NeutralObject* strategy);
    bool operator>>(IUnit& unit);

private:
    Point point;
    NeutralPlayer* player;
    NeutralObject* strategy;
};
