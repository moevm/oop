//
// Created by anton on 11.04.2020.
//

#ifndef OOP_1_ADAPTER_H
#define OOP_1_ADAPTER_H

#include <sstream>
#include "Logger.h"
#include "Units/Unit.h"
#include "Base.h"
#include "ProxyLogger.h"

class Base;

class Adapter: public ProxyLogger {
public:
    void attack(Unit*, int);

    void move(Unit*);

    void setUnit(Unit*);

    void setBase(Base*);

    void deleteUnit(Unit*);

    void logChanged(std::string);

    void save();

    void load();

};


#endif //OOP_1_ADAPTER_H
