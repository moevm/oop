#ifndef OOP_GAMER_H
#define OOP_GAMER_H
#include "Objects/Base.h"
#include <string>
#include <utility>

class Gamer {
public:
    explicit Gamer(std::string name) : name(std::move(name)) {};
    std::string getGamerName() {return name;};
private:
    std::string name;
};
#endif //OOP_GAMER_H
