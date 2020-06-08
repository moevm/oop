#ifndef BATTLEFORHONOUR_LOADCOMMAND_H
#define BATTLEFORHONOUR_LOADCOMMAND_H


#include "../LoadCI.h"

class LoadCommand: public Command {

private:

    std::ifstream fs;
    LoadCI inter;

public:

    explicit LoadCommand(std::string &filename): fs(filename){}
    void execute(GameState &gameState) override{

        gameState.newGame();
        std::string terminal;
        std::hash<std::string> toHash;
        unsigned long int calculatedHash = 0;
        unsigned long int fileHash = 0;

        std::string fileHashStr;
        std::getline(fs, fileHashStr);

        fileHash = convertStr(fileHashStr);

        while (std::getline(fs, terminal)){

            std::unique_ptr<Command> command = inter.handle(terminal);
            try {
                command->execute(gameState);
            } catch(DoubleBasePlacingExc &exception) {
                Log::log << "[#FileLoader]" << "User " << exception.playerIndex << " trying to place second base." << Log::logend;
            } catch (DoublePlacingExc &exception){
                Log::log << "[#FileLoader]" << "This cell is busy by other object." << Log::logend;
            } catch (OutOfRangeExc &exception){
                Log::log << "[#FileLoader]" << "Out of range. Cell " << exception.x << " " << exception.y << " is not exist." << Log::logend;
            } catch (ImpossibleMoveExc &exception){
                Log::log << "[#FileLoader]" << "Can't move to this cell. They busy by other object." << Log::logend;
            } catch (...){
                Log::log << "[#FileLoader]" << "Unknown error." << Log::logend;
            }
            auto snapshot = command->getSnapshot();
            gameState.addAction(snapshot);
            calculatedHash += snapshot->getHash(toHash);
            gameState.nextUser();

        }

        Log::log << "String hash: " << fileHashStr << Log::logend;
        Log::log << "Integer hash: " << fileHash << Log::logend;
        Log::log << "Calculated hash: " << calculatedHash << Log::logend;
        Log::log << "Commands were read: " << gameState.getActions().size() << Log::logend;

        if (fileHash != calculatedHash){
            Log::log << "Wrong file format. File may be incorrect." << Log::logend;
            throw InvalidFileLoadExc();
        }

    }

    ~LoadCommand() override{
        fs.close();
    }

};

class LoadCommandHandler: public CommandHandler{

public:

    bool isHandle(std::vector<std::string> &terminal) override{
        return terminal.size() == 2 && terminal[0] == "load";
    }

    std::unique_ptr<Command> handle(std::vector<std::string> &terminal) override{

        if (isHandle(terminal)){
            return std::unique_ptr<Command>(new LoadCommand(terminal[1]));
        }

        if (next)
            return next->handle(terminal);

        return std::make_unique<Command>();

    }

};



#endif //BATTLEFORHONOUR_LOADCOMMAND_H
