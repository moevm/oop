#ifndef LABOOP_CREATEUNITCOMMAND_HPP
#define LABOOP_CREATEUNITCOMMAND_HPP

#include "Command.hpp"

class CreateUnitCommand : public Command{
public:
    void execute(GameField *gameField) final {
        std::cout << "1. Create Infantry." << std::endl;
        std::cout << "2. Create Guardsmen." << std::endl;
        std::cout << "3. Create Fighter." << std::endl;
        std::cout << "4. Create Tank." << std::endl;
        std::cout << "5. Create Scout." << std::endl;
        std::cout << "6. Create Cannon." << std::endl;
        int choice;
        std::cin >> choice;
        if (choice < 1 || choice > 6){
            std::cout << "Incorrect choice." << std::endl; return;
        }
        int x, y;
        std::cout << "Units coordinate:\nx:";
        std::cin >> x;
        std::cout << "y:";
        std::cin >> y;
        if (x < 0 || y < 0 || x > gameField->getWidth()-1 || y > gameField->getHeight() -1){
            std::cout << "Incorrect coordinates." << std::endl; return;
        }
        switch (choice){
            case 1:
                gameField->createUnit(INFANTRY, x, y);
                break;
            case 2:
                gameField->createUnit(GUARDSMEN, x, y);
                break;
            case 3:
                gameField->createUnit(FIGHTER, x, y);
                break;
            case 4:
                gameField->createUnit(TANK, x, y);
                break;
            case 5:
                gameField->createUnit(SCOUT, x, y);
                break;
            case 6:
                gameField->createUnit(CANNON, x, y);
                break;
        }
    }
};


#endif //LABOOP_CREATEUNITCOMMAND_HPP
