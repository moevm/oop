#include <iostream>
#include "Field.h"
#include "Iterator.h"
#include "Base.h"
#include "Poisen.h"
#include "Potion.h"
#include "DrinkStrong.h"
#include "DrinkStamina.h"
#include "Handler.h"
#include "Facade.h"

int main() {

    Facade* facade = new Facade();
    std::string command;

    while(true) {
        std::cout << "Enter your command: " << std::endl;
        std::cin >> command;
        if (command == "createGame")
            facade->createGame();
        else if (command == "play")
            facade->play();
        else
            std::cout << "There is no such command" << std::endl;
    }

    return 0;
}
