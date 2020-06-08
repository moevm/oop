#ifndef GFIELD_H
#define GFIELD_H

#include "unit.h"
#include "landscape.h"
#include "land.h"
#include "swamp.h"
#include "forest.h"
#include "positivecard.h"
#include "negativecard.h"
//#include "deathcard.h"
#include "transformationcard.h"
#include <vector>

class GField{
private:
    int length, width;
    int numberUnit;
    Landscape* landscape;
    Land* land;
    Swamp* swamp;
    PositiveCard* positivcard;
    NegativeCard* negativcard;
    TransformationCard* transformationcard;
    //DeathCard* deathcard;
    Forest* forest;
    const int maxnumberUnit = 7;
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
    void addLabdscape();
    void addNeutralObject(std::string);
    int getLength();
    Land* getLand();
    Landscape* getLandscape();
};

#endif // GFIELD_H
