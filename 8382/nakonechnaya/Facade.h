#ifndef OOP_FACADE_H
#define OOP_FACADE_H
#include "Manager.h"

class Facade {
public:
    explicit Facade(){
        manager = new Manager;
    };
    void startGame(Rules *rules);
    void makeAction();
    void createGamer();
    ~Facade() {
        delete manager;
    };
protected:
    Manager *manager;
};
#endif //OOP_FACADE_H
