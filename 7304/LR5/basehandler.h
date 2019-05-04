#ifndef BASEHANDLER_H
#define BASEHANDLER_H

#include "ihandler.h"
#include <iostream>
#include <sstream>

template <typename T, typename U>
class BaseHandler : public IHandler <T>, public Unit, public HandlerOutput<U>{
protected:
    std::unique_ptr<T[]> inputs;
    std::size_t curInpCount;

    BaseHandler()
        : Unit(0,0),
          HandlerOutput<U>(0),
          inputs(nullptr),
          curInpCount(0)
    {
    }
    BaseHandler(std::size_t noInp, std::size_t noOut)
        : Unit(noInp, noOut),
          HandlerOutput<U>(noOut),
          inputs(new T[noInp]),
          curInpCount(0)
    {
    }

public :
    virtual void setNext(std::size_t slot, IHandler<U>* handler){
        this->nexts[slot] = handler;
    }

    virtual void setNext(std::size_t slot, std::shared_ptr<IHandler<U>> handler){
        this->nexts[slot] = handler.get();
    }

    virtual void handle (T inp) {
        // take input
        inputs[curInpCount] = inp;
        curInpCount++;
        //process
        if(curInpCount==this->noInp){
            // enough input, start processing then push to next in chain (the input counter is reset upon started processing)
            curInpCount = 0;
            process(this->noInp, this->inputs.get(), this->noOut, this->results.get());
            if(!this->isOutput){
                for(std::size_t i = 0; i<this->noOut;i++){
                    this->nexts[i]->handle(this->results[i]);
                }
            }
        }else{
            // not enough input
        }
    }

    virtual bool verify() const{
        if(this->isOutput) return true;
        for(std::size_t i = 0;i<this->noOut;i++){
            if(this->nexts[i]==nullptr){
                return false;
            }else{
                bool nextValid = dynamic_cast<Unit*>(this->nexts[i])->verify();
                if(!nextValid) return false;
            }
        }
        return true;
    }

    virtual void process(std::size_t, const T*, std::size_t , U *) = 0;

    friend std::ostream & operator << (std::ostream &out, const BaseHandler &h){
        out<< "Handler (id="<<h.id<<") ("<<(h.verify()?"valid":"invalid")<<") ";
        out<< "(out? "<<h.isOutput<<"): ";
        for(std::size_t i = 0; i<h.noOut; i++){
            out<<h.results[i]<<" ";
        }
        return out<<std::endl;
    }

    virtual std::string toString(){
        std::stringstream ss;
        ss<<"Id: "<<this->id<<"\t\t";
        ss<<"Num. input:  "<<this->noInp<<"\t\t";
        ss<<"Num. output: "<<this->noOut<<std::endl;
        ss<<"\t\t"<<"Is output? "<<this->isOutput;
        ss<<"\t\t"<<"Status: "<<(this->verify()?"valid":"invalid")<<std::endl;
        ss<<"\t\t"<<"Nexts: ";
        for(std::size_t i = 0;i<this->noOut;i++){
            IHandler<U> *u = this->nexts[i];
            if(u!=nullptr){
                ss<<"\t"<<(dynamic_cast<Unit*>(u)->id);
            }else{ss<<"\t";}
        }
        ss<<std::endl;

        ss<<"\t\t"<<"State: ";
        for(std::size_t i = 0;i<noOut;i++){
            U u = this->results[i];
            ss<<"\t"<<u;
        }
        ss<<std::endl;


        return ss.str();
    }

    virtual ~BaseHandler(){}
};

template <typename T>
class SimpleHandler : public BaseHandler <T,T>{
protected:
    SimpleHandler(int noInp, int noOut) : BaseHandler<T,T>(noInp,noOut){}
    virtual std::string toString(){
        return BaseHandler<T,T>::toString();
    }
};
#endif // BASEHANDLER_H
