#ifndef DERIVEDHANDLERS_H
#define DERIVEDHANDLERS_H

#include "basehandler.h"
#include <cmath>
#include "coordinate.h"

class SumHandler : public SimpleHandler<double>{
public:
    SumHandler() : SimpleHandler(2,1){this->type=1;}
    virtual void process(std::size_t, const double *inputs, std::size_t, double *outputs){
        outputs[0] = inputs[0]+inputs[1];
    }
    virtual std::string toString(){
        return SimpleHandler<double>::toString()+"\t\tType: SumHandler\n";
    }
    virtual Unit* clone() {
        return new SumHandler;
    }

};

class SquaredHandler : public SimpleHandler<double> {
public:
    SquaredHandler() : SimpleHandler(1,1) {this->type=2;}
    virtual void process(std::size_t, const double *inputs, std::size_t, double *outputs){
        outputs[0] = inputs[0]*inputs[0];
    }
    virtual std::string toString(){
        return SimpleHandler<double>::toString()+"\t\tType: SquaredHandler\n";
    }
    virtual Unit* clone() {
        return new SquaredHandler;
    }
};

class DivModHandler : public SimpleHandler<int> {
public:
    DivModHandler() : SimpleHandler(2,2) {this->type=3;}
    virtual void process(std::size_t, const int *inputs, std::size_t, int *outputs){
        outputs[0] = inputs[0]/inputs[1];
        outputs[1] = inputs[0]%inputs[1];
    }
    virtual std::string toString(){
        return SimpleHandler<int>::toString()+"\t\tType: DivModHandler\n";
    }
    virtual Unit* clone() {
        return new DivModHandler;
    }
};

class DistributeHandler : public SimpleHandler<Coordinate>{
public:
    DistributeHandler() : SimpleHandler(1,2){this->type=4;}
    virtual void process(std::size_t, const Coordinate *inputs, std::size_t, Coordinate *outputs){
        outputs[0] = inputs[0];
        outputs[1] = inputs[0];
    }
    virtual std::string toString(){
        return SimpleHandler<Coordinate>::toString()+"\t\tType: DistributeHandler\n";
    }
    virtual Unit* clone() {
        return new DistributeHandler;
    }
};


class CoordinateBreakUpHandler : public BaseHandler<Coordinate, double>{
public:
    CoordinateBreakUpHandler() : BaseHandler(1,2){this->type=5;}
    virtual void process(std::size_t, const Coordinate *inputs, std::size_t, double *outputs){
        outputs[0] = inputs[0].x;
        outputs[1] = inputs[0].y;
    }
    virtual std::string toString(){
        return BaseHandler<Coordinate,double>::toString()+"\t\tType: CoordinateBreakupHandler\n";
    }
    virtual Unit* clone() {
        return new CoordinateBreakUpHandler;
    }
};


class DistanceHandler : public BaseHandler<Coordinate, double>{
public:
    DistanceHandler() : BaseHandler(1,1){this->type=6;}
    virtual void process(std::size_t, const Coordinate *inputs, std::size_t, double *outputs){
        outputs[0] = sqrt(inputs[0].x*inputs[0].x + inputs[0].y*inputs[0].y);
    }
    virtual std::string toString(){
        return BaseHandler<Coordinate,double>::toString()+"\t\tType: DistanceHandler\n";
    }
    virtual Unit* clone() {
        return new DistanceHandler;
    }
};

class CoordinateMakingHandler : public BaseHandler<double, Coordinate>{
public:
    CoordinateMakingHandler() : BaseHandler(2,1){this->type = 7;}
    virtual void process(std::size_t, const double *inputs, std::size_t, Coordinate *outputs){
        outputs[0].x = inputs[0];
        outputs[0].y = inputs[1];
    }
    virtual std::string toString(){
        return BaseHandler<double,Coordinate>::toString()+"\t\tType: CoordinateMakingHandler\n";
    }
    virtual Unit* clone() {
        return new CoordinateMakingHandler;
    }
};

class RoundHandler : public BaseHandler<double, int>{
public:
    RoundHandler() : BaseHandler(2,2){this->type = 7;}
    virtual void process(std::size_t, const double *inputs, std::size_t, int *outputs){
        outputs[0] = round(inputs[0]);
        outputs[1] = round(inputs[1]);
    }
    virtual std::string toString(){
        return BaseHandler<double, int>::toString()+"\t\tType: RoundHandler\n";
    }
    virtual Unit* clone() {
        return new RoundHandler;
    }
};

#endif // DERIVEDHANDLERS_H
