#ifndef OOP_PROXY_H
#define OOP_PROXY_H
#include "Grass.h"
#include "Forest.h"
#include "Mountains.h"
#include "Swamp.h"

class Proxy : public Landscape{
public:
    explicit Proxy(Land land);
    void changeAttribute(Unit *unit) override;
    char getName() final {};
    Land getLandName() final {};
private:
    Landscape *landscape;
};
#endif //OOP_PROXY_H
