#ifndef COMMAND_H
#define COMMAND_H

#include <exception>
#include <string>

class EntityInterface;
class Entity;

class CellInterface;
class Cell;
enum class Team;

class Logger;

class Command
{
    std::string abstract_name = "unnamed command";
public:
    struct empty_interface: public std::exception{
    private:
        const char* msg;
    public:
        size_t code;
        empty_interface(const char *msg, size_t code = 0):
            msg(msg), code(code) {}

        const char * what() const throw(){
            return msg;
        }
    };
    virtual ~Command(){}
    virtual bool execute(Logger *logger) = 0;
    virtual const std::string& name() const
    {return abstract_name;}

    virtual Team getTeam() const = 0;
    virtual int getScore() const
    {return 0;}
};

#endif // COMMAND_H
