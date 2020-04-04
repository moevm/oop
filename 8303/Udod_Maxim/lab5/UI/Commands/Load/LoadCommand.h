//
// Created by shenk on 02.04.2020.
//

#ifndef UNTITLED13_LOADCOMMAND_H
#define UNTITLED13_LOADCOMMAND_H

#include "../../LoadCommandInterpreter.h"

class LoadCommand: public Command {

private:

    std::ifstream fs;
    LoadCommandInterpreter interpreter;

public:

    explicit LoadCommand(std::string &filename): fs(filename){}
    void execute(GameInfo &gameInfo) override{

        gameInfo.newGame();

        std::string cmd;
        while (std::getline(fs, cmd)){

            CommandPtr command = interpreter.handle(cmd);
            command->execute(gameInfo);
            gameInfo.addToHistory(command->getMemento());
            gameInfo.nextUser();

        }

    }

    ~LoadCommand() override{

        fs.close();

    }

};

class LoadCommandHandler: public CommandHandler{

public:

    bool canHandle(std::vector<std::string> &cmd) override{

        return cmd.size() == 2 && cmd[0] == "load";

    }

    CommandPtr handle(std::vector<std::string> &cmd) override{

        if (canHandle(cmd)){
            return CommandPtr(new LoadCommand(cmd[1]));
        }

        if (next) return next->handle(cmd);

        return std::make_unique<Command>();

    }

};


#endif //UNTITLED13_LOADCOMMAND_H
