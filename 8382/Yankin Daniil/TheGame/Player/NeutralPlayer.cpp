#include "NeutralPlayer.h"
#include "Neutrals/NeutralContext.h"

NeutralPlayer::~NeutralPlayer() {
    for (auto object = neutralObjectSet.begin(); object != neutralObjectSet.end(); object = neutralObjectSet.begin()) {
        auto temp = *object;
        neutralObjectSet.erase(object);
        delete temp;
    }
}

void NeutralPlayer::addNeutralObject(NeutralContext* neutralObject) {
    neutralObjectSet.insert(neutralObject) ;
}

void NeutralPlayer::removeNeutralObject(NeutralContext* neutralObject) {
    neutralObjectSet.erase(neutralObject) ;
}

std::set <NeutralContext*>* NeutralPlayer::getNeutralObjectSet() {
    return &neutralObjectSet;
}
