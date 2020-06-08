#ifndef BATTLEFORHONOUR_CREATEUNITCOMMAND_H
#define BATTLEFORHONOUR_CREATEUNITCOMMAND_H


#include "Command.h"
#include "../../Objects/Units/Infantry/SwordMan.h"
#include "../../Objects/Units/Archer/CrossBowMan.h"
#include "../../Objects/Units/Druid/Hermit.h"
#include "../../Objects/Units/Archer/LongBowMan.h"

class CreateUnitCommand: public Command {

private:

    Point unitPos;
    UnitType unitType;

public:

    explicit CreateUnitCommand(Point position, UnitType unitType): unitPos(position), unitType(unitType){}
    void execute(GameState &gameState) override{

        if (!gameState.getNowPlayerBase()){
            Log::log << "Can't create a unit without a base" << Log::logend;
            return;
        }

        switch (unitType) {

            case UnitType::ARCHER:
                gameState.getNowPlayerBase()->createUnit<LongBowMan>(unitPos);
                break;
            case UnitType::INFANTRY:
                gameState.getNowPlayerBase()->createUnit<SwordMan>(unitPos);
                break;
            case UnitType::DRUID:
                gameState.getNowPlayerBase()->createUnit<Hermit>(unitPos);
                break;

        }
        Log::log << "Command to create a unit " << Log::logend;

    }

    [[nodiscard]] CommandSnapshot * getSnapshot() const override{

        std::stringstream stream;
        stream << "create unit " << unitPos.x << " " << unitPos.y << " " << static_cast<int>(unitType) << std::endl;
        return new CommandSnapshot(stream.str());

    }

};

class CreateUnitCommandHandler: public CommandHandler {

public:

    bool isHandle(std::vector<std::string> &terminal) override{

        return terminal.size() == 4 && terminal[0] == "unit";

    }

    std::unique_ptr<Command> handle(std::vector<std::string> &terminal) override {

        if (isHandle(terminal)){
            int x = convertStr(terminal[1]);
            int y = convertStr(terminal[2]);
            auto type = static_cast<UnitType>(std::stoi(terminal[3]));
            Point basePos(x, y);
            return std::unique_ptr<Command>(new CreateUnitCommand(basePos, type));
        }

        if (next)
            return next->handle(terminal);
        return std::make_unique<Command>();

    }

};


#endif //BATTLEFORHONOUR_CREATEUNITCOMMAND_H
