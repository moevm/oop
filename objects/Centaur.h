#ifndef CENTAUR_H
#define CENTAUR_H
#include "Rider.h"

class Centaur : public Rider {
public:
    explicit Centaur(std::string = "");
    explicit Centaur(const Centaur&);
    Centaur(Centaur&&);
    std::string type() const final;
};


#endif //CENTAUR_H
