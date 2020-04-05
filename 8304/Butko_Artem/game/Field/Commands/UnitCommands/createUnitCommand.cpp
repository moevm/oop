//
// Created by Artem Butko on 04/04/2020.
//

#include "createUnitCommand.h"

void createUnitCommand::gameCommand()
{
    std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*" << std::endl;
    std::cout << "'C' - Crossbowman" << std::endl;
    std::cout << "'A' - Archer" << std::endl;
    std::cout << "'W' - Witch" << std::endl;
    std::cout << "'M' - Mage" << std::endl;
    std::cout << "'K' - Knight" << std::endl;
    std::cout << "'S' - Spearman" << std::endl;
    std::cout << "*-*-*-*-*-*-*-*-*-*-*-*-*" << std::endl;
    std::cout << " id = ";
    std::cin >> id_;
    Field->base_->createUnit(id_);
}
