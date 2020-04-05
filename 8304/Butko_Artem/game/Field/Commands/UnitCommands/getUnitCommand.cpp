//
// Created by Artem Butko on 04/04/2020.
//

#include "getUnitCommand.h"

void getUnitCommand::gameCommand()
{
    std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*" << std::endl;
    std::cout << "'C' - Crossbowman" << std::endl;
    std::cout << "'A' - Archer" << std::endl;
    std::cout << "'W' - Witch" << std::endl;
    std::cout << "'M' - Mage" << std::endl;
    std::cout << "'K' - Knight" << std::endl;
    std::cout << "'S' - Spearman" << std::endl;
    std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*" << std::endl;
    std::cout << "Unit id  = ";
    std::cin >> id_;
    std::cout << "Quantity = ";
    std::cin >> quantity_;
    std::cout << "Unit  x  = ";
    std::cin >> x_;
    std::cout << "Unit  y  = ";
    std::cin >> y_;
    Field->addObject(Field->base_->getUnit(id_,quantity_), x_, y_);
}
