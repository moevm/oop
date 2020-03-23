//
// Created by andrei on 02.03.2020.
//

#ifndef OOP_LAB1_NEUTRAL_H
#define OOP_LAB1_NEUTRAL_H

class Neutral {
public:
    virtual int getX() = 0;

    virtual void setX(int newX) = 0;

    virtual int getY() = 0;

    virtual void setY(int newY) = 0;

    virtual char getType() = 0;
};


#endif //OOP_LAB1_NEUTRAL_H
