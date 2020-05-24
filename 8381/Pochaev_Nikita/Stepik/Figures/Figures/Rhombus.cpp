#include "Rhombus.h"

#include <utility>

Rhombus::Rhombus(ANSIColor::eCOLOR_CODE color, const std::vector<BasePoint>& vertex_) : Shape(vertex_, color) {
    calcCenter();
}

eFIGURE Rhombus::getType() const {
    return RHOMBUS;
}

std::string Rhombus::getDescription() const {
    std::string res{};
    res.append(ANSIColor::coloredString("Rhombus:", color->getColor()));
    res.append("\n\tCenter: " + std::to_string(center->getX()) + ";" + std::to_string(center->getY()) + ")");
    res.append("\n\tSide length: " + std::to_string(sideLength) + "\n");

    return res;
}

void Rhombus::calcCenter() {
    if(vertex.size() != 4) {
        throw std::invalid_argument("Wrong count of vertex for rhombus!");
    }

    if(vertex[0].getX() == vertex[1].getX()) {
        center->setX(vertex[0].getX());
        center->setY(vertex[2].getX());
    } else {
        center->setX(vertex[2].getX());
        center->setY(vertex[0].getX());
    }
}

void Rhombus::move(std::vector<BasePoint> newVertex) {
    if(newVertex.size() != 4) {
        throw std::invalid_argument("Wrong count of vertex for Rhombus move!");
    }
    for(int i = 0; i < 4; i++) {
        vertex[i] = newVertex[i];
    }
    calcCenter();
}

void Rhombus::rotate(float angle) {
    for(auto &curr : vertex) {
        curr.setY(curr.getY() * std::cos(angle) - curr.getX() * std::sin(angle));
        curr.setX(curr.getY() * std::sin(angle) + curr.getX() * std::cos(angle));
    }
}

void Rhombus::scale(float factor) {
    if(factor <= PRECISION) {
        throw std::invalid_argument("Factor can't be less zero!");
    }

    vertex[0].setX(vertex[0].getX() * 1/2 * factor);
    vertex[1].setX(vertex[1].getX() * 1/2 * factor);

    vertex[2].setX(vertex[2].getY() * 1/2 * factor);
    vertex[3].setX(vertex[3].getY() * 1/2 * factor);

    calcCenter();
}

