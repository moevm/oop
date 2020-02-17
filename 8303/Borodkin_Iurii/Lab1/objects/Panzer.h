#ifndef PANZER_H
#define PANZER_H
#include "Rider.h"

class Panzer : public Rider {
public:
    explicit Panzer(std::pair<int, int>, std::string = "");
    std::string type() const final;
};


#endif //PANZER_H
