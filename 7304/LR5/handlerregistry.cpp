#include "handlerregistry.h"

HandlerRegistry* HandlerRegistry::instance = nullptr;
HandlerRegistry::HandlerRegistry()
{
    handlers.insert(std::pair<std::string,Unit*>("CoordinateMaking",new CoordinateMakingHandler));
    handlers.insert(std::pair<std::string,Unit*>("Distribute",new DistributeHandler));
    handlers.insert(std::pair<std::string,Unit*>("Distance",new DistanceHandler));
    handlers.insert(std::pair<std::string,Unit*>("CoordinateBreakUp",new CoordinateBreakUpHandler));
    handlers.insert(std::pair<std::string,Unit*>("Squared",new SquaredHandler));
    handlers.insert(std::pair<std::string,Unit*>("Sum",new SumHandler));
    handlers.insert(std::pair<std::string,Unit*>("Round",new RoundHandler));
    handlers.insert(std::pair<std::string,Unit*>("DivMod",new DivModHandler));

}

Unit* HandlerRegistry::getByName(std::string name){
    auto res = handlers.find(name);
    if(res!=handlers.end()){
        return res->second->clone();
    }
    return nullptr;
}
