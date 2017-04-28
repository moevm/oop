//
//  Rectangle.h
//  WORKPLEASE
//
//  Created by user on 30.03.17.
//  Copyright © 2017 user. All rights reserved.
//

#ifndef Rectangle_h
#define Rectangle_h
#include "point.h"
#include "iostream"
#include "figure.h"

using namespace std;
class Rectangle : public Shape

{
    
protected:
    Point upperLeft;
    double width;
    double height;
    
public:
    
    Rectangle(const Point &upperLeft, double width, double height, double angle);
    void move_to(const Point &p) override;
    void rotate (double angle) override;
    void scale(double scale = 1) override;
    void print(std::ostream& os) const override;
    
    std::vector<Point> getVertices() const override;
};
#endif /* Rectangle_h */
