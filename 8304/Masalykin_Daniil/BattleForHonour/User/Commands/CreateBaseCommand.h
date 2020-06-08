#ifndef BATTLEFORHONOUR_CREATEBASECOMMAND_H
#define BATTLEFORHONOUR_CREATEBASECOMMAND_H


#include "Command.h"
#include "../../Armor/ArmorFlyweight.h"
#include "../../Armor/Armor.h"

class CreateBaseCommand: public Command {

private:

    Point basePos;

public:

    explicit CreateBaseCommand(Point pos): basePos(pos){}
    void execute(GameState &gameState) override{

        auto *base = new Base(100, *ArmorFlyweight::getFlyweight<LeatherArmor>());
        if (gameState.setNowPlayerBase(base)) {
            gameState.getField().addBase(base, basePos);
            Log::log << "Command to create base" << Log::logend;
        } else
            Log::log << "This player already has base" << Log::logend;
    }

    [[nodiscard]] CommandSnapshot * getSnapshot() const override{

        std::stringstream stream;
        stream << "create base " << basePos.x << " " << basePos.y << std::endl;
        return new CommandSnapshot(stream.str());

    }

};

class CreateBaseCommandHandler: public CommandHandler{

public:

    bool isHandle(std::vector<std::string> &terminal) override{

        return terminal.size() == 3 && terminal[0] == "base";

    }

    std::unique_ptr<Command> handle(std::vector<std::string> &terminal) override {

        if (isHandle(terminal)){
            int x = convertStr(terminal[1]);
            int y = convertStr(terminal[2]);
            Point basePosition(x, y);
            return std::unique_ptr<Command>(new CreateBaseCommand(basePosition));
        }

        if (next)
            return next->handle(terminal);

        return std::make_unique<Command>();
    }
};



#endif //BATTLEFORHONOUR_CREATEBASECOMMAND_H
