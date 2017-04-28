//
//  Square.h
//  WORKPLEASE
//
//  Created by user on 30.03.17.
//  Copyright © 2017 user. All rights reserved.
//

#ifndef Square_h
#define Square_h

#include "rectangle.h"
#include "iostream"
#include "figure.h"

using namespace std;

class Square : public Rectangle

{
public:
    Square(const Point &upperLeft, double side, double fi):
        Rectangle(upperLeft, side, side, fi) {}
};
#endif /* Square_h */
