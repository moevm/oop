//
// Created by shenk on 16.03.2020.
//

#ifndef UNTITLED13_CREATEUNITCOMMAND_H
#define UNTITLED13_CREATEUNITCOMMAND_H


#include "../Command.h"
#include "../../../Objects/Units/Infantry/SwordMan.h"
#include "../../../Objects/Units/Archer/CrossBowMan.h"
#include "../../../Objects/Units/Wizard/FireMage.h"

class CreateUnitCommand: public Command {

private:

    Point unitPosition;
    UnitType unitType;

public:

    explicit CreateUnitCommand(Point position, UnitType unitType): unitPosition(position), unitType(unitType){}
    virtual void execute(GameInfo &gameInfo, GameField &gameField){

        if (!gameInfo.getNowPlayerBase()){
            std::cout << "Can't create unit without base" << std::endl;
            return;
        }

        switch (unitType) {

            case UnitType::INFANTRY:
                gameInfo.getNowPlayerBase()->createUnit<SwordMan>(unitPosition);
                break;
            case UnitType::ARCHER:
                gameInfo.getNowPlayerBase()->createUnit<CrossBowMan>(unitPosition);
                break;
            case UnitType::WIZARD:
                gameInfo.getNowPlayerBase()->createUnit<FireMage>(unitPosition);
                break;

        }

    }

};

class CreateUnitCommandHandler: public CommandHandler {

public:

    CommandPtr handle(std::vector<std::string> &cmd) override {

        if (cmd.size() != 3){
            std::cout << "Wrong command" << std::endl;
            return CommandPtr(new Command);
        }

        int x = std::stoi(cmd[0]);
        int y = std::stoi(cmd[1]);
        auto type = static_cast<UnitType>(std::stoi(cmd[2]));
        Point basePosition(x, y);
        return CommandPtr(new CreateUnitCommand(basePosition, type));

    }

};


#endif //UNTITLED13_CREATEUNITCOMMAND_H
