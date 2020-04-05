//
// Created by Artem Butko on 04/04/2020.
//

#include "moveUnitCommand.h"

void moveUnitCommand::gameCommand()
{
    std::cout << "from  x  = ";
    std::cin >> x1_;
    std::cout << "from  y  = ";
    std::cin >> y1_;
    std::cout << "to    x  = ";
    std::cin >> x2_;
    std::cout << "to    y  = ";
    std::cin >> y2_;
    Field->moveObject(x1_, y1_, x2_, y2_);
}
