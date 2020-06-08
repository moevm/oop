#ifndef BATTLEFORHONOUR_STACKEXCEPTIONS_H
#define BATTLEFORHONOUR_STACKEXCEPTIONS_H


#include <exception>


class DoubleBasePlacingExc: std::exception {

public:

    int playerIndex;
    explicit DoubleBasePlacingExc(int playerIndex): playerIndex(playerIndex){}

};

class OutOfRangeExc: std::exception {

public:
    int x;
    int y;
    OutOfRangeExc(int x, int y): x(x), y(y){}
};

class DoublePlacingExc: std::exception {

};

class ImpossibleMoveExc: std::exception {

};

class InvalidFileLoadExc: std::exception {

};




#endif //BATTLEFORHONOUR_STACKEXCEPTIONS_H
