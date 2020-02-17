#ifndef SPEARMAN_H
#define SPEARMAN_H
#include "ShortRange.h"

class SpearMan : public ShortRange {
public:
    explicit SpearMan(std::pair<int, int>, std::string = "");
    std::string type() const final;
};


#endif //SPEARMAN_H
