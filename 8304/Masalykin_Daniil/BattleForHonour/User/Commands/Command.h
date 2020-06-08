#ifndef BATTLEFORHONOUR_COMMAND_H
#define BATTLEFORHONOUR_COMMAND_H


#include <string>
#include <memory>
#include <sstream>
#include "../../Logs/Log.h"
#include "../../Game/GameState.h"
#include "CommandSnapshot.h"

class Command {

public:

    virtual void execute(GameState &gameInfo){}
    [[nodiscard]] virtual CommandSnapshot *getSnapshot() const {
        return new CommandSnapshot(">>wrong command\n");
    }
    virtual ~Command(){}

};


class CommandHandler{

protected:
    CommandHandler *next{};

public:

    virtual std::unique_ptr<Command> handle(std::vector<std::string> &terminal)=0;
    virtual bool isHandle(std::vector<std::string> &terminal)=0;
    void setNext(CommandHandler *commandHandler){
        next = commandHandler;
    }
    virtual ~CommandHandler()= default;

};

int convertStr(const std::string& s) {

    try {
        return (int)std::stoull(s);
    } catch (std::invalid_argument) {
        Log::log << "Wrong format. No numbers." << Log::logend;
        return 0;
    } catch (std::out_of_range) {
        Log::log << "Wrong format. Range overflow." << Log::logend;
        return 0;
    } catch (...) {
        Log::log << "Wrong format. Anything goes wrong..." << Log::logend;
        return 0;
    }

}


#endif //BATTLEFORHONOUR_COMMAND_H
