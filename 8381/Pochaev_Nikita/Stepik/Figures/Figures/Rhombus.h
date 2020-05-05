#ifndef STEPIC_RHOMBUS_H
#define STEPIC_RHOMBUS_H

#include "Shape.h"

class Rhombus final : public Shape {
private:
    float sideLength{};
    void calcCenter() override;
public:
    ~Rhombus() override = default;
    Rhombus(ANSIColor::eCOLOR_CODE color, const std::vector<BasePoint> &vertex_);

    // Geometry object interface realization
    eFIGURE getType() const override;
    std::string getDescription() const override;

    // Main task functions
    void move(std::vector<BasePoint> newVertex) override;
    void rotate(float angle) override;
    void scale(float factor) override;
};

#endif //STEPIC_RHOMBUS_H
