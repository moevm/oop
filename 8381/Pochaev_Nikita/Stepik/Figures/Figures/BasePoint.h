#ifndef STEPIC_BASEPOINT_H
#define STEPIC_BASEPOINT_H

#include <iostream>
#include <cmath>
#include <memory>

#include "../Subsidiary/IGeometricObject.h"

class BasePoint : public IGeometryObject {
public:
    ~BasePoint() override = default;
    BasePoint(int x_, int y_);
    BasePoint(const BasePoint& point);
    BasePoint& operator= (const BasePoint& point);
    BasePoint(BasePoint&& point) noexcept;
    BasePoint& operator= (BasePoint&& point) noexcept;
    eFIGURE getType() const override;
    std::string getDescription() const override;

    float getX();
    float getY();
    void setX(float x_);
    void setY(float y_);

private:
    float x{}, y{};   // position
};

#endif //STEPIC_BASEPOINT_H
