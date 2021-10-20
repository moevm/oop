//
// Created by shenk on 16.03.2020.
//

#ifndef UNTITLED13_SHOWUNITCOMMAND_H
#define UNTITLED13_SHOWUNITCOMMAND_H

#include "../Command.h"

class ShowUnitCommand: public Command {

private:

    Point unitPosition;

public:

    explicit ShowUnitCommand(Point p): unitPosition(p){}
    void execute(GameInfo &gameInfo) override{

        auto object = gameInfo.getField().getCell(unitPosition)->getObject();
        if (object && object->getType() == ObjectType::UNIT){

            auto unit = dynamic_cast<Unit*>(object);
            std::cout << "Unit info: " << std::endl
            << "\tHP: " << unit->getHealth() << std::endl
            << "\tWeapon: " << unit->getWeapon() << std::endl
            << "\tArmor: " << unit->getArmor() << std::endl;

            game::log << "Command show unit" << game::logend;

        } else{
            game::log << "Empty cell" << game::logend;
        }

    }

};

class ShowUnitCommandHandler: public CommandHandler{

public:

    bool canHandle(std::vector<std::string> &cmd) override{

        return cmd.size() == 3 && cmd[0] == "unit";

    }

    virtual CommandPtr handle(std::vector<std::string> &cmd){

        if (canHandle(cmd)){
            int x = utils::StrToInt(cmd[1]);
            int y = utils::StrToInt(cmd[2]);
            Point unitPosition(x, y);
            return CommandPtr(new ShowUnitCommand(unitPosition));
        }

        if (next) return next->handle(cmd);

        return std::make_unique<Command>();

    }

};


#endif //UNTITLED13_SHOWUNITCOMMAND_H
