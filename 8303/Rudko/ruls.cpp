#include "ruls.h"

void Ruls::Ruls1(){
    facade = new Facade;
    facade->NewGame(10, 6);
}

void Ruls::Ruls2(){
    facade = new Facade;
    facade->NewGame(7, 3);
}
