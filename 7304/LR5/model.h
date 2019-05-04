
#ifndef MODEL_H
#define MODEL_H
#include <type_traits>
#include "basehandler.h"
#include "ihandler.h"
#include "myexception.h"
#include "coordinate.h"
#include "reader.h"
#include "writer.h"
template <typename T, typename U>
class Model : public IMultiInputHandler<T>, public BaseHandler <T,U>{
protected:
    std::vector<std::shared_ptr<Unit>> handlers;
    IHandler<T> *inputHandler;
    HandlerOutput<U> *outputHandler;

    std::map<std::size_t, std::vector<Memento*>> history;
public:
    using IMultiInputHandler<T>::handle;
    Model() : BaseHandler<T,U>(), inputHandler(nullptr), outputHandler(nullptr){}

    template <typename A, typename B>
    std::shared_ptr<BaseHandler<A,B>> add(BaseHandler<A,B> *h){
        std::shared_ptr<BaseHandler<A,B>> sp (h);
        handlers.push_back(sp);
        return sp;
    }

    bool contains(Unit *unit){
        bool isManaged = false;
        for(const auto &h : handlers){
            if(h.get()->id==unit->id){
                isManaged = true;
                break;
            }
        }
        return isManaged;
    }

    std::vector<std::shared_ptr<Unit>> getManagedHandlers(){
        return handlers;
    }
    template <typename X>
    void setInput(BaseHandler<T,X> *handler){
        //check if h is in handlers
        if(this->contains(handler)){
            inputHandler = handler;
            this->noInp = handler->noInp;
            // log about success
        }else{
            // log about failure
        }
    }

    template <typename X, typename Y>
    void replace(Unit* h1, Unit *h2){
        BaseHandler<X,Y>* bh1 = dynamic_cast<BaseHandler<X,Y>*>(h1);
        BaseHandler<X,Y>* bh2 = dynamic_cast<BaseHandler<X,Y>*>(h2);
        if(bh1==nullptr||bh2==nullptr) throw TypeException();
        replace(bh1,bh2);
    }
    template <typename X, typename Y>
    void replace(BaseHandler<X,Y> *h1, BaseHandler<X,Y> *h2){
        if(h1->noInp!=h2->noInp) throw HandlerStructureException();
        if(h1->noOut!=h2->noOut) throw HandlerStructureException();
        if(h1->id==h2->id) return;
        if(!this->contains(h1)||!this->contains(h2)) return;
        for(std::shared_ptr<Unit> &h : handlers){
            HandlerOutput<X>* h_out = dynamic_cast<HandlerOutput<X>*>(h.get());
            if(h_out!=nullptr){
                for(std::size_t i = 0; i<h->noOut;i++){
                    if(h_out->getNext(i)!=nullptr){
                        if(h_out->getNext(i)==h1){
                            h_out->setNext(i,h2);
                        }
                    }
                }
            }
        }
        if(this->outputHandler!=nullptr&&this->outputHandler==dynamic_cast<HandlerOutput<U>*>(h1)) {
            this->outputHandler = dynamic_cast<HandlerOutput<U>*>(h2);
            h2->isOutput = true;
        }
        else{
            h2->isOutput = h1->isOutput;
            h1->isOutput = true; // set to true to pass the verify test
            for(std::size_t i = 0;i<h1->noOut;i++){
                h2->setNext(i,h1->getNext(i));
                h1->setNext(i,nullptr);
            }

        }

        if(dynamic_cast<Unit*>(this->inputHandler)->id==h1->id){
            this->inputHandler = dynamic_cast<IHandler<T>*>(h2);
        }

    }

    template <typename X>
    void setOutput(BaseHandler<X,U> *handler){
        // check if r is in handlers
        if(this->contains(handler)){
            outputHandler = handler;
            handler->isOutput = true;

            this->noOut = handler->noOut;
            this->nexts.reset(new IHandler<U>*[this->noOut]);
        }
    }

    void backup(){
        for(const auto &h :handlers){
            IBackupable *target = dynamic_cast<IBackupable*>(h.get());
            if(target!=nullptr){
                Memento *m = target->makeBackup();
                history[h->id].push_back(m);
            }
        }
    }

    void undo(){
        for(const auto &h :handlers){
            IBackupable *target = dynamic_cast<IBackupable*>(h.get());
            if(history.find(h->id)!=history.end()){
                if(!history[h->id].empty()){
                    Memento *m = history[h->id].back();
                    target->restore(m);
                    history[h->id].pop_back();
                }
            }
        }

    }

    virtual bool verify() const{
        if(inputHandler==nullptr || this->noOut==0 || this->noInp == 0) return false;
        else{
            return  dynamic_cast<Unit*>(inputHandler)->verify() && BaseHandler<T,U>::verify();
        }
    }
    virtual void handle(T inp){
        if(this->verify()){
            if(inputHandler!=nullptr)
            {
                inputHandler->handle(inp);
                // TODO: forward all results to nexts
                if(!this->isOutput){
                    for(std::size_t i = 0; i<this->noOut;i++){
                        this->nexts[i]->handle(outputHandler->getResult()[i]);
                    }
                }
            }
        }

    }

    virtual U* getResult() const {
        return outputHandler->getResult();
    }

    friend std::ostream & operator << (std::ostream &out, const Model &h){
        out<< "Model (id="<<h.id<<") ("<<(h.verify()?"valid":"invalid")<<"): ";
        for(std::size_t i = 0; i<h.noOut; i++){
            out<<h.getResult()[i]<<" ";
        }
        return out<<std::endl;
    }

    template <typename R ,typename = typename std::enable_if<std::is_base_of<IReader, R>::value, R>::type>
    void loadFromFile(std::string fileName){
        R reader(fileName);
        for(auto handler : this->handlers){
            reader>>handler.get();
        }
    }

    template <typename R ,typename = typename std::enable_if<std::is_base_of<IWriter, R>::value, R>::type>
    void saveToFile(std::string fileName){
        R writer(fileName);
        for(auto handler : this->handlers){
            writer<<handler.get();
        }
    }

    virtual std::string toString(){
        std::stringstream ss;
        ss<<"Id: "<<this->id<<"\t\t";
        ss<<"Num. input:  "<<this->noInp<<"\t\t";
        ss<<"Num. output: "<<this->noOut<<std::endl;
        ss<<"\t\t"<<"Status: "<<(this->verify()?"valid":"invalid")<<std::endl;
        ss<<"\t\t"<<"State: ";
        for(std::size_t i = 0;i<this->noOut;i++){
            U u = this->getResult()[i];
            ss<<"\t"<<u;
        }
        ss<<std::endl;


        return ss.str();
    }
private:
    virtual void process(std::size_t, const T*, std::size_t , U *){}
};




#endif // MODEL_H
