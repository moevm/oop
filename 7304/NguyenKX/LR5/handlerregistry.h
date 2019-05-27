#ifndef HANDLERREGISTRY_H
#define HANDLERREGISTRY_H

#include <map>
#include "ihandler.h"
#include "derivedhandlers.h"
class HandlerRegistry
{
private:
    std::map<std::string,Unit*> handlers;
    static HandlerRegistry *instance;
    HandlerRegistry();
public:
    static HandlerRegistry& getInstance(){
        if(instance==nullptr) instance = new HandlerRegistry;
        return *instance;
    }
    Unit* getByName(std::string name);
};

#endif // HANDLERREGISTRY_H
