//
// Created by shenk on 02.04.2020.
//

#ifndef UNTITLED13_SAVECOMMAND_H
#define UNTITLED13_SAVECOMMAND_H


#include "../Command.h"

class SaveCommand: public Command {

private:

    std::ofstream fs;

public:

    explicit SaveCommand(std::string &filename): fs(filename){

        game::log << "File opened" << game::logend;
        game::log << "File is open: " << fs.is_open() << game::logend;

    }
    void execute(GameInfo &gameInfo) override{

        game::log << "Saving..." << game::logend;
        auto history = gameInfo.getHistory();
        for (auto m: history){

            m->saveToFile(fs);

        }

    }

    ~SaveCommand() override{
        game::log << "File closed" << game::logend;
        fs.close();
        game::log << "File is open: " << fs.is_open() << game::logend;
    }

};

class SaveCommandHandler: public CommandHandler{

    bool canHandle(std::vector<std::string> &cmd) override{

        return cmd.size() == 2 && cmd[0] == "save";

    }

    CommandPtr handle(std::vector<std::string> &cmd) override{

        if (canHandle(cmd)){
            return CommandPtr(new SaveCommand(cmd[1]));
        }

        if (next) return next->handle(cmd);

        return std::make_unique<Command>();

    }

};


#endif //UNTITLED13_SAVECOMMAND_H
