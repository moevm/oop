//
// Created by andrei on 22.03.2020.
//

#include "neutral.h"

#ifndef OOP_LAB1_MAINNEUTRAL_H
#define OOP_LAB1_MAINNEUTRAL_H


class MainNeutral: public Neutral {
public:
    MainNeutral(int x = 0, int y = 0);

    int getX() override;

    void setX(int newX) override;

    int getY() override;

    void setY(int newY) override;

protected:
    int x, y;
};


#endif //OOP_LAB1_MAINNEUTRAL_H
