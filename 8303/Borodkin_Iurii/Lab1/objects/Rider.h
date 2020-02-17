#ifndef RIDER_H
#define RIDER_H
#include "Unit.h"

class Rider : public Unit {
public:
    enum Moves {
        STEP3_BACK = -3,
        STEP2_BACK     , STEP1_BACK   ,
        STAY           , STEP1_FORWARD,
        STEP2_FORWARD  , STEP3_FORWARD
    };
    explicit Rider(std::pair<int, int>, std::string = "");
    std::string type() const override;
    void moveX(Moves);
    void moveY(Moves);
};


#endif //RIDER_H
