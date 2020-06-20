
#ifndef UNTITLED13_DOUBLEBASEPLACINGEXCEPTION_H
#define UNTITLED13_DOUBLEBASEPLACINGEXCEPTION_H
#include <exception>

class DoubleBasePlacingException: std::exception {

public:

    int playerIndex;
    explicit DoubleBasePlacingException(int playerIndex): playerIndex(playerIndex){}

};
#endif //UNTITLED13_DOUBLEBASEPLACINGEXCEPTION_H
