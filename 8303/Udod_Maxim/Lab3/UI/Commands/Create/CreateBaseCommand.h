//
// Created by shenk on 16.03.2020.
//

#ifndef UNTITLED13_CREATEBASECOMMAND_H
#define UNTITLED13_CREATEBASECOMMAND_H

#include "../Command.h"
#include "../../../Armor/ArmorFlyWeight.h"
#include "../../../Armor/LeatherArmor.h"

class CreateBaseCommand: public Command {

private:

    Point basePosition;

public:

    explicit CreateBaseCommand(Point position): basePosition(position){}
    void execute(GameInfo &gameInfo, GameField &gameField) override{

        auto *base = new Base(100, *ArmorFlyWeight::getFlyWeight<LeatherArmor>());
        if (gameInfo.setNowPlayerBase(base))
            gameField.addBase(base, basePosition);
        else
            std::cout << "This player already has base" << std::endl;

    }

};

class CreateBaseCommandHandler: public CommandHandler{

public:

    CommandPtr handle(std::vector<std::string> &cmd) override {

        int x = std::stoi(cmd[0]);
        int y = std::stoi(cmd[1]);
        Point basePosition(x, y);
        return CommandPtr(new CreateBaseCommand(basePosition));

    }
};


#endif //UNTITLED13_CREATEBASECOMMAND_H
