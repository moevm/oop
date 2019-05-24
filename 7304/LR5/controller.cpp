#include "controller.h"
#include "model.h"
#include "coordinate.h"
#include "basehandler.h"
#include <iostream>
#include "derivedhandlers.h"
#include <memory>
#include "handlerregistry.h"
Controller::Controller(){
    init();

}

void Controller::init(){
    //auto h1 = myModel.add(new CoordinateMakingHandler);
    auto h1 = myModel.add(HandlerRegistry::getInstance().getByName("CoordinateMaking"));
    auto h2 = myModel.add(HandlerRegistry::getInstance().getByName("Distribute"));
    auto h3 = myModel.add(HandlerRegistry::getInstance().getByName("Distance"));
    auto h4 = myModel.add(HandlerRegistry::getInstance().getByName("CoordinateBreakUp"));
    auto h5 = myModel.add(HandlerRegistry::getInstance().getByName("Squared"));
    auto h6 = myModel.add(HandlerRegistry::getInstance().getByName("Sum"));
    auto h7 = myModel.add(HandlerRegistry::getInstance().getByName("Round"));
    auto h8 = myModel.add(HandlerRegistry::getInstance().getByName("DivMod"));

//    auto h3 = myModel.add(new DistanceHandler);
//    auto h4 = myModel.add(new CoordinateBreakUpHandler);
//    auto h5 = myModel.add(new SquaredHandler);
//    auto h6 = myModel.add(new SumHandler);
//    auto h7 = myModel.add(new RoundHandler);
//    auto h8 = myModel.add(new DivModHandler);

    auto h6_dup = myModel.add(new SumHandler);
    h6_dup->isOutput = true;

    h1->setNext(0,h2);

    h2->setNext(0,h3);
    h2->setNext(1,h4);

    h3->setNext(0,h5);

    h4->setNext(0,h6);
    h4->setNext(1,h6);

    h5->setNext(0,h7);

    h6->setNext(0,h7);

    h7->setNext(0,h8);

    h7->setNext(1,h8);

    myModel.isOutput = true;
    myModel.setInput(dynamic_cast<Unit*>(h1.get()));
    myModel.setOutput(dynamic_cast<Unit*>(h8.get()));
//        auto h1 =  myModel.add(new CoordinateBreakUpHandler);
//        auto h2 = myModel.add(new SumHandler);
//        auto h3 = myModel.add(new SumHandler);
//        auto h4 = myModel.add(new DistributeHandler);

//        h1->isOutput = false;
//        h1->setNext(0,h2);
//        h1->setNext(1,h2);

//        myModel.setInput(h1.get());
//        myModel.setOutput(h2.get());
}

std::vector<std::size_t> Controller::getUnitIds(){
    std::vector<std::size_t> ids;
    for(std::shared_ptr<Unit> &h : myModel.getManagedHandlers()){
        ids.push_back(h->id);
    }
    return std::vector<std::size_t>(ids);
}

std::vector<std::pair<std::size_t,std::size_t>> Controller::getConnections()
{
    std::vector<std::pair<std::size_t,std::size_t>> connections;
    for(std::shared_ptr<Unit> &h : myModel.getManagedHandlers()){
        for(auto &nxt : h->getNexts()){
            connections.push_back(std::pair<std::size_t,std::size_t>(h->id,nxt));
        }
    }
    return std::vector<std::pair<std::size_t,std::size_t>>(connections);

}
void Controller::replace(std::size_t id1, std::size_t id2){
    Unit* unit1 = nullptr;
    Unit* unit2 = nullptr;
    for(std::shared_ptr<Unit> &h : myModel.getManagedHandlers()){
        if(h->id==id1) unit1 = h.get();
        if(h->id==id2) unit2 = h.get();
    }
    if(unit1!=nullptr&&unit2!=nullptr){
        switch(unit1->type){
        case 1:
        case 2:
        case 4:
            myModel.replace<double,double>(unit1,unit2);
            break;

        case 3:
            myModel.replace<int,int>(unit1,unit2);
            break;
        case 5:
        case 6:
            myModel.replace<Coordinate, double>(unit1,unit2);
            break;
        default:
            throw TypeException();

        }
    }


}

void Controller::backup(){
    myModel.backup();
}

void Controller::handle(double c1,double c2){
    myModel.backup();
    double *arr = new double[2];
    arr[0] = c1;
    arr[1] = c2;
    myModel.handle(2,arr);
//        myModel.handle(c1);
//        myModel.handle(c2);
}

void Controller::undo(){
    myModel.undo();
}
std::string Controller::getModelState(){
    return myModel.toString();
}
std::map<std::size_t,std::string> Controller::getHandlersInfo(){
    std::map<std::size_t,std::string> result;
    for(std::shared_ptr<Unit> h : myModel.getManagedHandlers()){
        //std::cout<<h->toString();
        result.insert(std::pair<std::size_t,std::string>(h->id,h.get()->toString()));
    }
    return result;
}

void Controller::loadFromTextFile(std::string path){
    myModel.loadFromFile<TxtReader>(path);
}

void Controller::loadFromBinFile(std::string path){
    myModel.loadFromFile<BinaryReader>(path);
}

void Controller::saveToTextFile(std::string path){
    myModel.saveToFile<TxtWriter>(path);
}

void Controller::saveToBinFile(std::string path){
    myModel.saveToFile<BinaryWriter>(path);
}
