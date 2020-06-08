#include "commands_queue.h"

#include <iostream>

#include "game_elements/commands/command.h"

#include "game.h"
#include "logger.h"

//CommandsQueue::CommandsQueue(Game &game):
//    game(game)
//{}


CommandsQueue::~CommandsQueue(){
    while(!commands.empty()){
        delete commands.front();
        commands.pop();
    }
}


void CommandsQueue::push(Command *cmd){
    commands.push(cmd);
}


std::pair<int, int> CommandsQueue::apply(Logger *logger){
    std::pair<int, int> points;

    while(!commands.empty()){

        if(logger)
            (*logger) << commands.front()->name() << ":\n{\n";

        bool good;
        if((good = commands.front()->execute(logger)) == 1)
        {
            if(commands.front()->getTeam() == Team::Red){
                points.first += commands.front()->getScore();
            }
            if(commands.front()->getTeam() == Team::Blu){
                points.second += commands.front()->getScore();
            }
        }

        if (logger)
                (*logger) << "} : " << ((good)?"success":"fault\n");

        delete commands.front();
        commands.pop();
    }

    return points;
}


size_t CommandsQueue::size() const{
    return commands.size();
}


bool CommandsQueue::empty() const{
    return commands.empty();
}
