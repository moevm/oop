#ifndef SPEARMAN_H
#define SPEARMAN_H
#include "ShortRange.h"

class SpearMan : public ShortRange {
public:
    explicit SpearMan(std::string = "");
    explicit SpearMan(const SpearMan&);
    SpearMan(SpearMan&&);
    std::string type() const final;
};


#endif //SPEARMAN_H
