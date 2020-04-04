#include "NeutralContext.h"
#include "Player/NeutralPlayer.h"


NeutralContext::NeutralContext(Point point, NeutralPlayer* player) : point(point), player(player), strategy(nullptr) {
    player->addNeutralObject(this);
}

NeutralContext::~NeutralContext() {
    delete strategy;
    player->removeNeutralObject(this);
}


uint8_t NeutralContext::getGroupType() {
    return NEUT_OBJECT;
}

uint8_t NeutralContext::getObjectType() {
    return NEUT_OBJECT;
}

Point NeutralContext::getPoint() {
    return point;
}


void NeutralContext::setStrategy(NeutralObject* strategy) {
    delete this->strategy;
    this->strategy = strategy;
}

bool NeutralContext::operator>>(IUnit& unit) {
    if (strategy != nullptr)
        return (*strategy >> unit);
    return true;
}
