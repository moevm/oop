#include "NeutralPlayer.h"


void NeutralPlayer::addNeutralObject(NeutralContext* neutralObject) {
    neutralObjectSet.insert(neutralObject) ;
}

void NeutralPlayer::removeNeutralObject(NeutralContext* neutralObject) {
    neutralObjectSet.erase(neutralObject) ;
}

std::set <NeutralContext*>* NeutralPlayer::getNeutralObjectSet() {
    return &neutralObjectSet;
}
