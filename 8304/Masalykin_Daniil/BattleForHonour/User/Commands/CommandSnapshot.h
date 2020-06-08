#ifndef BATTLEFORHONOUR_COMMANDSNAPSHOT_H
#define BATTLEFORHONOUR_COMMANDSNAPSHOT_H


#include <string>
#include <fstream>
#include <utility>

class CommandSnapshot{

private:

    std::string commandLine;

public:

    explicit CommandSnapshot(std::string commandLine): commandLine(std::move(commandLine)){}

    void saveToFile(std::ofstream &fs) const{

        fs << commandLine;

    }

    unsigned long int getHash(std::hash<std::string> &toHash){
        return toHash(commandLine);
    }

};


#endif //BATTLEFORHONOUR_COMMANDSNAPSHOT_H
