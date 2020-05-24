#include "Trapezoid.h"

#include <cmath>

void Trapezoid::calcSides() {
    if(vertex[0].getY() == vertex[1].getY()) {
        if(std::fabs(vertex[0].getX() - vertex[1].getX()) > std::fabs(vertex[2].getX() - vertex[3].getX())) {
            longSideLength = std::fabs(vertex[0].getX() - vertex[1].getX());
            shortSideLength = std::fabs(vertex[2].getX() - vertex[3].getX());
        }
    } else {
        if(std::fabs(vertex[0].getX() - vertex[2].getX()) > std::fabs(vertex[1].getX() - vertex[3].getX())) {
            longSideLength = std::fabs(vertex[0].getX() - vertex[2].getX());
            shortSideLength = std::fabs(vertex[1].getX() - vertex[3].getX());
        }
    }
}

Trapezoid::Trapezoid(ANSIColor::eCOLOR_CODE color, const std::vector<BasePoint> &vertex_) {
    calcSides();
}

eFIGURE Trapezoid::getType() const {
    return TRAPEZE;
}

std::string Trapezoid::getDescription() const {
    std::string res{};
    res.append(ANSIColor::coloredString("Trapezoid:", color->getColor()));
    res.append("\n\tCenter: " + std::to_string(center->getX()) + ";" + std::to_string(center->getY()) + ")");
    res.append("\n\tShort side: " + std::to_string(shortSideLength) + "; Long side: " + std::to_string(longSideLength) + "\n");

    return res;
}

void Trapezoid::move(std::vector<BasePoint> newVertex) {
    if(newVertex.size() != 4) {
        throw std::invalid_argument("Wrong count of vertex for Trapezoid move!");
    }
    for(int i = 0; i < 4; i++) {
        vertex[i] = newVertex[i];
    }
    calcSides();
}

void Trapezoid::rotate(float angle) {
    for(auto &curr : vertex) {
        curr.setY(curr.getY() * std::cos(angle) - curr.getX() * std::sin(angle));
        curr.setX(curr.getY() * std::sin(angle) + curr.getX() * std::cos(angle));
    }
}

void Trapezoid::scale(float factor) {
    if(factor <= PRECISION) {
        throw std::invalid_argument("Factor can't be less zero!");
    }

    vertex[0].setX(vertex[0].getX() * 1/2 * factor);
    vertex[1].setX(vertex[1].getX() * 1/2 * factor);

    vertex[2].setX(vertex[2].getY() * 1/2 * factor);
    vertex[3].setX(vertex[3].getY() * 1/2 * factor);

    calcSides();
}
