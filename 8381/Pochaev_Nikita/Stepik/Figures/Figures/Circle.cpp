#include "Circle.h"

Circle::Circle(int xCenter, int yCenter, float radius_, ANSIColor::eCOLOR_CODE color_) : radius(radius_) {
    color = std::make_unique<ANSIColor>(color_);
    center = std::make_shared<BasePoint>(xCenter, yCenter);
}

eFIGURE Circle::getType() const {
    return CIRCLE;
}

std::string Circle::getDescription() const {
    std::string res{};
    res.append(ANSIColor::coloredString("Circle:", color->getColor()));
    res.append("\n\tCenter: " + std::to_string(center->getX()) + ";" + std::to_string(center->getY()) + ")");
    res.append("\n\tRadius: " + std::to_string(radius) + "\n");

    return res;
}

void Circle::move(std::vector<BasePoint> newVertex) {
    if(newVertex.size() != 1) {
        throw std::invalid_argument("Wrong count if vertex for circle move!");
    }

    center = std::make_shared<BasePoint>(newVertex[0]);
}

void Circle::scale(float factor) {
    radius *= factor;
}


