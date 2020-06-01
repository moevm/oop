#ifndef GFIELD_H
#define GFIELD_H

#include "unit.h"
#include <vector>

class GField{
private:
    int length, width;
    int numberUnit;
    const int maxnumberUnit = 5;
    //Unit*** map;


public:

    std::vector<std::vector<Unit*>> map1;

    GField(const GField &gfield);

    GField(int , int );
    void addUnit(Unit*, int, int);
    void moveUnite(Unit* , int , int);
    void deleteUnite(Unit*);
    void printField();
    int getMaxUnit();
    int getNumUnit();
    void setNumUnit(int);
    std::vector<std::vector<Unit*>> getMap();
    void setMap(std::vector<std::vector<Unit*>>);
};

#endif // GFIELD_H
