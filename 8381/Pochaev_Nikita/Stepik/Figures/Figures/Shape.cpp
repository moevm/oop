#include "Shape.h"

Shape::Shape(std::vector<BasePoint> vertex_, ANSIColor::eCOLOR_CODE color_) :
    vertex(std::move(vertex_)), color(std::make_unique<ANSIColor>(color_)) { };

std::shared_ptr<BasePoint> Shape::getCenter() {
    return center;
}

void Shape::calcCenter() { }

void Shape::move(std::vector<BasePoint> newVertex) { }

void Shape::rotate(float angle) { }

void Shape::scale(float factor) { }

void Shape::setColor(ANSIColor::eCOLOR_CODE color_) {
    color->setColor(color_);
}

std::string Shape::getColor() {
    return ANSIColor::convertFGEnumToStr(color->getColor());
}

eFIGURE Shape::getType() const {
    return BASIC_SHAPE;
}

std::string Shape::getDescription() const {
    return "";
}

std::ostream &operator<<(std::ostream &out, const Shape &shape) {
    out << shape.getDescription();
    return out;
}