#include <iostream>

#include "Figures/Circle.h"

int main() {
    auto fig = new Circle(5, 5, 4, ANSIColor::FG_BLUE);
    std::cout << *fig;
    fig->setColor(ANSIColor::FG_MAGENTA);
    fig->scale(0.5);
    std::cout << *fig;
    std::vector<BasePoint> newCoord = { BasePoint(2, 3) };
    fig->move(newCoord);
    std::cout << *fig;

    return 0;
}
