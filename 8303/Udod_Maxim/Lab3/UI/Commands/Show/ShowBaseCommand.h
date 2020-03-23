//
// Created by shenk on 16.03.2020.
//

#ifndef UNTITLED13_SHOWBASECOMMAND_H
#define UNTITLED13_SHOWBASECOMMAND_H


#include "../Command.h"
#include "../../../Point.h"

class ShowBaseCommand: public Command {

private:

    Point basePosition;

public:

    explicit ShowBaseCommand(Point p): basePosition(p){}
    virtual void execute(GameInfo &gameInfo, GameField &gameField){

        auto object = gameField.getCell(basePosition)->getObject();
        if (object && object->getType() == ObjectType::BASE){

            auto base = dynamic_cast<Base*>(object);
            std::cout << "Base info: " << std::endl
                      << "\tHP: " << base->getHealth() << std::endl
                      << "\tArmor: " << base->getArmor() << std::endl
                      << "\tMax Objects Count: " << base->getMaxObjectsCount() << std::endl;

        } else{
            std::cout << "Empty Cell" << std::endl;
        }

    }

};

class ShowBaseCommandHandler: public CommandHandler {

public:

    CommandPtr handle(std::vector<std::string> &cmd) override{

        int x = std::stoi(cmd[0]);
        int y = std::stoi(cmd[1]);
        Point basePosition(x, y);
        return CommandPtr(new ShowBaseCommand(basePosition));

    }

};


#endif //UNTITLED13_SHOWBASECOMMAND_H
