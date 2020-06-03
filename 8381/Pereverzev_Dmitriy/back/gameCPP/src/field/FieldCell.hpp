
#ifndef FieldCell_hpp
#define FieldCell_hpp

#include <stdio.h>
#include "../objects/Object.hpp"
#include "../landscape/Landscape.hpp"
#include "../landscape/landscapeProxy/LandscapeProxy.hpp"

class FieldCell
{
private:
    Object *object;
    Landscape *landscape;
    

public:
    FieldCell();
    FieldCell(Object *object, Landscape *landscape);
    ~FieldCell();
    void setObject(Object *object);
    void setLandscape(Landscape *landscape);
    Object *getObject();
    Landscape *getLandscape();
};

#endif /* FieldCell_hpp */
