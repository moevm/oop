#ifndef STEPIC_TRAPEZOID_H
#define STEPIC_TRAPEZOID_H

#include "Shape.h"

class Trapezoid final : public Shape {
private:
    float shortSideLength{};
    float longSideLength{};
    void calcSides();
public:
    ~Trapezoid() override = default;
    Trapezoid(ANSIColor::eCOLOR_CODE color, const std::vector<BasePoint> &vertex_);

    // Geometry object interface realization
    eFIGURE getType() const override;
    std::string getDescription() const override;

    // Main task functions
    void move(std::vector<BasePoint> newVertex) override;
    void rotate(float angle) override;
    void scale(float factor) override;
};

#endif //STEPIC_TRAPEZOID_H
