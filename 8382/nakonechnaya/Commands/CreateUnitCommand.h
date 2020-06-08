#ifndef OOP_CREATEUNITCOMMAND_H
#define OOP_CREATEUNITCOMMAND_H
#include "Command.h"
#include "GameException.h"

class CreateUnitCommand : public Command{
public:
    void execute(GameField *gameField, Base *base, LogProxy *logger, Base *enemyBase) final {
        std::cout << "1. Create Halberdier." << std::endl;
        std::cout << "2. Create Skeleton." << std::endl;
        std::cout << "3. Create Archer." << std::endl;
        std::cout << "4. Create Lich." << std::endl;
        std::cout << "5. Create Griffin." << std::endl;
        std::cout << "6. Create Bone Dragon." << std::endl;
        int choice;
        std::cin >> choice;
        if (choice < 1 || choice > 6){
            std::cout << "Incorrect choice." << std::endl; return;
        }
        int x, y;

        int count = 0;
        while (count < 3){

            std::cout << "New coordinate:\nx:";
            std::cin >> x;
            std::cout << "y:";
            std::cin >> y;
            if (x < 0 || y < 0 || x > gameField->getWidth()-1 || y > gameField->getHeight()-1){
                std::cout << "Incorrect coordinates." << std::endl;
                throw GameException("CreateUnitCommand.cpp ", 1, "execute ", "Entered coordinates are outside the field\n");
            }
            else if (base->getCoordinates()->x == x && base->getCoordinates()->y == y){
                std::cout << "Incorrect coordinates." << std::endl;
            }
            else if (enemyBase->getCoordinates()->x == x && enemyBase->getCoordinates()->y == y){
                std::cout << "Incorrect coordinates." << std::endl;
            }
            else if (abs(base->getCoordinates()->x - x) > 1 || abs(base->getCoordinates()->y - y) > 1){
                std::cout << "Too far. Enter new coordinates: " << std::endl;
                std::cout << "x:";
                std::cin >> x;
                std::cout << "y:";
                std::cin >> y;
            }
            else {
                break;
            }
            count++;
        }
        if (count == 3){
            std::cout << "Failed to create unit." << std::endl;
            return;
        }

        switch (choice){
            case 1:
                gameField->createUnit(HALBERDIER, x, y, base);
                break;
            case 2:
                gameField->createUnit(SKELETON, x, y, base);
                break;
            case 3:
                gameField->createUnit(ARCHER, x, y, base);
                break;
            case 4:
                gameField->createUnit(LICH, x, y, base);
                break;
            case 5:
                gameField->createUnit(GRIFFIN, x, y, base);
                break;
            case 6:
                gameField->createUnit(BONE_DRAGON, x, y, base);
                break;
        }
        if (logger->getFormat() == 1) {
            auto adapter = new Adapter(gameField);
            adapter->setLogger(logger);
            adapter->setLog(gameField->getLogString());
            adapter->print();
        } else {
            logger->setLog(gameField->getLogString());
            logger->print();
        }
    }
};
#endif //OOP_CREATEUNITCOMMAND_H
