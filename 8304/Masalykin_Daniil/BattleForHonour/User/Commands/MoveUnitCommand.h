#ifndef BATTLEFORHONOUR_MOVEUNITCOMMAND_H
#define BATTLEFORHONOUR_MOVEUNITCOMMAND_H


#include "Command.h"

class MoveUnitCommand: public Command {

private:

    Point from;
    Point to;

public:

    MoveUnitCommand(Point from, Point to):
        from(from),
        to(to){}
    void execute(GameState &gameInfo) override{

        auto object = gameInfo.getField().getCell(from)->getObject();
        if (object && object->getType() == ObjectType::UNIT){
            auto unit1 = dynamic_cast<Unit *>(object);
            unit1->move(to);
            Log::log << "Command to unit moved" << Log::logend;
        } else
            Log::log << "No unit on this cell" << Log::logend;
    }

    [[nodiscard]] CommandSnapshot * getSnapshot() const override{

        std::stringstream stream;
        stream << "move unit " << from.x << " " << from.y << " " << to.x << " " << to.y << std::endl;
        return new CommandSnapshot(stream.str());

    }

};

class MoveUnitCommandHandler: public CommandHandler {

public:

    bool isHandle(std::vector<std::string> &terminal) override{

        return terminal.size() == 5 && terminal[0] == "unit";

    }

    std::unique_ptr<Command> handle(std::vector<std::string> &terminal) override{

        if (isHandle(terminal)){

            int x1 = convertStr(terminal[1]);
            int y1 = convertStr(terminal[2]);
            int x2 = convertStr(terminal[3]);
            int y2 = convertStr(terminal[4]);
            Point from(x1, y1);
            Point to(x2, y2);
            return std::unique_ptr<Command>(new MoveUnitCommand(from, to));
        }

        if (next)
            return next->handle(terminal);

        return std::make_unique<Command>();

    }

};

#endif //BATTLEFORHONOUR_MOVEUNITCOMMAND_H
