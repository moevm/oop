#ifndef OOP_STRATEGY_H
#define OOP_STRATEGY_H
#include "../units/Unit.h"

class Strategy {
public:
    virtual ~Strategy(){};
    virtual void changeAttributes(Unit &unit) = 0;
};

class UnitContext{
public:
    UnitContext(Strategy *strategy = nullptr) : strategy(strategy) {};
    ~UnitContext() {delete strategy;};
    void setStrategy(Strategy *strategy) {delete this->strategy; this->strategy = strategy;};
    void changeUnitsAttributes(Unit &unit) {this->strategy->changeAttributes(unit);};
private:
    Strategy *strategy;
};

class HospitalStrategyPeople : public Strategy{
public:
    void changeAttributes(Unit &unit) override{
        unit.changeAttributes(0, 0, 100);
    }
};

class BarStrategy : public Strategy{
public:
    void changeAttributes(Unit &unit) override{
        unit.changeAttributes(100, 0, -20);
    }
};

class ShopStrategyOther : public Strategy{
public:
    void changeAttributes(Unit &unit) override{
        unit.changeAttributes(0, 100, 0);
    }
};

class TrainStrategyPeople : public Strategy{
public:
    void changeAttributes(Unit &unit) override{
        unit.changeAttributes(100, 0, -10);
    }
};

#endif //OOP_STRATEGY_H
