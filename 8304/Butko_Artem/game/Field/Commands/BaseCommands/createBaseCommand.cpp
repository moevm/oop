//
// Created by Artem Butko on 04/04/2020.
//

#include "createBaseCommand.h"

void createBaseCommand::gameCommand()
{
    std::cout << "Base x = ";
    std::cin >> x;
    std::cout << "Base y = ";
    std::cin >> y;
    std::cout << "Base limit = ";
    std::cin >> limit;
    Field->createBase(x, y, limit);
}
