#ifndef BATTLEFORHONOUR_SHOWUNITCOMMAND_H
#define BATTLEFORHONOUR_SHOWUNITCOMMAND_H


#include "Command.h"

class ShowUnitCommand: public Command {

private:

    Point unitPosition;

public:

    explicit ShowUnitCommand(Point p): unitPosition(p){}
    void execute(GameState &gameInfo) override{

        auto object = gameInfo.getField().getCell(unitPosition)->getObject();
        if (object && object->getType() == ObjectType::UNIT){

            auto unit = dynamic_cast<Unit*>(object);
            std::cout << "Unit: " << std::endl
                      << "HP: " << unit->getHealth() << std::endl
                      << "Armor: " << unit->getArmor() << std::endl
                      << "Weapon: " << unit->getWeapon() << std::endl
                      << "Unit class: ";
            switch(unit->getUnitType()){
                case UnitType::ARCHER:
                    std::cout << "Archer" << std::endl;
                    break;
                case UnitType::DRUID:
                    std::cout << "Druid" << std::endl;
                    break;
                case UnitType::INFANTRY:
                    std::cout << "Infantry" << std::endl;
                    break;
            }

            Log::log << "Command show unit" << Log::logend;

        } else{
            Log::log << "Empty cell" << Log::logend;
        }

    }

};

class ShowUnitCommandHandler: public CommandHandler{

public:

    bool isHandle(std::vector<std::string> &terminal) override{

        return terminal.size() == 3 && terminal[0] == "unit";

    }

    virtual std::unique_ptr<Command> handle(std::vector<std::string> &terminal){

        if (isHandle(terminal)){
            int x = convertStr(terminal[1]);
            int y = convertStr(terminal[2]);
            Point unitPosition(x, y);
            return std::unique_ptr<Command>(new ShowUnitCommand(unitPosition));
        }

        if (next)
            return next->handle(terminal);

        return std::make_unique<Command>();
    }

};



#endif //BATTLEFORHONOUR_SHOWUNITCOMMAND_H
