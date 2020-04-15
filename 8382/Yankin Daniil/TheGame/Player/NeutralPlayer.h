#pragma once

#include <cstdint>
#include <set>

class NeutralContext;


class NeutralPlayer
{
    friend class GameFacade;

public:
    void addNeutralObject(NeutralContext* neutralObject);
    void removeNeutralObject(NeutralContext* neutralObject);

private:
    std::set <NeutralContext*>* getNeutralObjectSet();

    std::set <NeutralContext*> neutralObjectSet;
};
