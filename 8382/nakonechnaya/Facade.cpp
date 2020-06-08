#include "Facade.h"

void Facade::startGame(Rules *rules) {
    manager->startGame(rules);
}

void Facade::makeAction() {
    manager->printMenu();
    manager->makeChoice();
}

void Facade::createGamer() {
    manager->createGamer();
}