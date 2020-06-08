#ifndef BATTLEFORHONOUR_SHOWBASECOMMAND_H
#define BATTLEFORHONOUR_SHOWBASECOMMAND_H


#include "Command.h"
#include "../../GameField/Point.h"

class ShowBaseCommand: public Command {

private:

    Point basePosition;

public:

    explicit ShowBaseCommand(Point p): basePosition(p){}
    void execute(GameState &gameInfo) override{

        auto object = gameInfo.getField().getCell(basePosition)->getObject();
        if (object && object->getType() == ObjectType::BASE){

            auto base = dynamic_cast<Base*>(object);
            std::cout << "Base: " << std::endl
                      << "HP: " << base->getHealth() << std::endl
                      << "Armor: " << base->getArmor() << std::endl
                      << "Max Objects Count: " << base->getMaxObjectsCount() << std::endl;
            Log::log << "Show base command" << Log::logend;

        } else{
            Log::log << "Empty cell" << Log::logend;
        }

    }

};

class ShowBaseCommandHandler: public CommandHandler {

public:

    bool isHandle(std::vector<std::string> &terminal) override{

        return terminal.size() == 3 && terminal[0] == "base";

    }

    std::unique_ptr<Command> handle(std::vector<std::string> &terminal) override{

        if (isHandle(terminal)){
            int x = convertStr(terminal[1]);
            int y = convertStr(terminal[2]);
            Point basePosition(x, y);
            return std::unique_ptr<Command>(new ShowBaseCommand(basePosition));
        }

        if (next)
            return next->handle(terminal);

        return std::make_unique<Command>();
    }

};


#endif //BATTLEFORHONOUR_SHOWBASECOMMAND_H
