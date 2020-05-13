//
// Created by kot on 09.05.2020.
//

#ifndef PROXY_H
#define PROXY_H

#include "../Units/unit.h"
#include "landscape.h"

class Proxy : public Landscape
{
private:
    Landscape* landscape;
    bool checkAccess();
    void logAccess();
public:
    Proxy(Landscape*);
    bool canMove(Unit*) const;
    bool canAttack(Unit*);
    ~Proxy();
    std::string getType() const;
};


#endif //PROXY_H
