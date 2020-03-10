#ifndef RIDER_H
#define RIDER_H
#include "Unit.h"

class Rider : public Unit {
protected:
    explicit Rider(std::string = "");
    std::string type() const override;
};


#endif //RIDER_H
