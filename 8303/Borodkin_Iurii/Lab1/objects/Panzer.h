#ifndef PANZER_H
#define PANZER_H
#include "Rider.h"

class Panzer : public Rider {
public:
    explicit Panzer(std::string = "");
    explicit Panzer(const Panzer&);
    Panzer(Panzer&&);
    std::string type() const final;
};


#endif //PANZER_H
