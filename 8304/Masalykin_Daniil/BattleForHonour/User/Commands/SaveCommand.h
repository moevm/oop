#ifndef BATTLEFORHONOUR_SAVECOMMAND_H
#define BATTLEFORHONOUR_SAVECOMMAND_H


#include "Command.h"

class SaveCommand: public Command {

private:

    std::ofstream fs;

public:

    explicit SaveCommand(std::string &filename){
        fs = std::ofstream(filename);
        Log::log << "File opened" << Log::logend;
        Log::log << "File is opened: " << fs.is_open() << Log::logend;

    }
    void execute(GameState &gameState) override{

        std::hash<std::string> toHash;
        unsigned long int fileHash = 0;

        Log::log << "Saving..." << Log::logend;

        auto actions = gameState.getActions();

        for (auto elem: actions){
            fileHash += elem->getHash(toHash);
        }

        fs << fileHash << std::endl;

        for (auto elem: actions){
            elem->saveToFile(fs);
        }

        Log::log << "Saved commands count: " << gameState.getActions().size() << Log::logend;

    }

    ~SaveCommand() override{
        Log::log << "File closed" << Log::logend;
        fs.close();
        Log::log << "File is opened: " << fs.is_open() << Log::logend;
    }

};

class SaveCommandHandler: public CommandHandler{

    bool isHandle(std::vector<std::string> &terminal) override{
        return terminal.size() == 2 && terminal[0] == "save";

    }

    std::unique_ptr<Command> handle(std::vector<std::string> &terminal) override{

        if (isHandle(terminal)){
            return std::unique_ptr<Command>(new SaveCommand(terminal[1]));
        }

        if (next)
            return next->handle(terminal);

        return std::make_unique<Command>();
    }

};


#endif //BATTLEFORHONOUR_SAVECOMMAND_H
