#include <iostream>
#include "Facade.h"

int main() {
    Facade* facade = new Facade();
    facade->startGame();
    facade->play();

    return 0;
}
