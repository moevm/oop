#ifndef CENTAUR_H
#define CENTAUR_H
#include "Rider.h"

class Centaur : public Rider {
public:
    explicit Centaur(std::pair<int, int>, std::string = "");
    std::string type() const final;
};


#endif //CENTAUR_H
