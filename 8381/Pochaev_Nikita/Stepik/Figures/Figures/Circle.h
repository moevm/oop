#ifndef STEPIC_CIRCLE_H
#define STEPIC_CIRCLE_H

#include "../Subsidiary/IGeometricObject.h"
#include "Shape.h"

class Circle final : public Shape {
private:
    float radius{};
public:
    ~Circle() override = default;
    Circle(int xCenter, int yCenter, float radius_, ANSIColor::eCOLOR_CODE color_);

    // Geometry object interface realization
    eFIGURE getType() const override;
    std::string getDescription() const override;

    // Shape interface realization
    void move(std::vector<BasePoint> newVertex) override;
    void scale(float factor) override;
};

#endif //STEPIC_CIRCLE_H
