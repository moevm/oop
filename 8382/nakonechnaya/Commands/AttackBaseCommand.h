#ifndef OOP_ATTACKBASECOMMAND_H
#define OOP_ATTACKBASECOMMAND_H
#include "Command.h"

class AttackBaseCommand : public Command{
public:
    void execute(GameField *gameField, Base *base, LogProxy *logger, Base *enemyBase) final {
        int x1, y1;
        std::cout << "Attacking unit coordinates:\nx:";
        std::cin >> x1;
        std::cout << "y:";
        std::cin >> y1;
        if (x1 < 0 || y1 < 0 || x1 > gameField->getWidth()-1 || y1 > gameField->getHeight() -1){
            std::cout << "Incorrect coordinates." << std::endl;
            return;
        }
        if (base->getUnit(x1, y1) == nullptr){
            std::cout << "It is not your unit." << std::endl;
            return;
        }
        int x2 = enemyBase->getCoordinates()->x;
        int y2 = enemyBase->getCoordinates()->y;
        if (abs(x1-x2) > 1 || abs(y1-y2) > 1){
            std::cout << "Enemy base is far from this unit." << std::endl;
            return;
        }
        gameField->attackBase(x1, y1, x2, y2, base, enemyBase);
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


#endif //OOP_ATTACKBASECOMMAND_H
