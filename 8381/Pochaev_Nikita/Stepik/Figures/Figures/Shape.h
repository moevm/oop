#ifndef STEPIC_SHAPE_H
#define STEPIC_SHAPE_H

#include <vector>
#include <utility>
#include <cmath>

#include "IShape.h"

class Shape : public IShape, IGeometryObject {
public:
    ~Shape() override = default;
    explicit Shape(std::vector<BasePoint> vertex_ = {}, ANSIColor::eCOLOR_CODE color_ = ANSIColor::FG_DEFAULT);
    std::shared_ptr<BasePoint> getCenter() override;

    // Geometry object interface realization
    eFIGURE getType() const override;
    std::string getDescription() const override;

    // Main task functions
    void move(std::vector<BasePoint> newVertex) override;
    void rotate(float angle) override;
    void scale(float factor) override;
    void setColor(ANSIColor::eCOLOR_CODE color_) override;
    std::string getColor() override;
    friend std::ostream& operator<< (std::ostream &out, const Shape &shape);

protected:
    std::unique_ptr<ANSIColor> color{};
    std::shared_ptr<BasePoint> center{};
    std::vector<BasePoint> vertex{};

    void calcCenter() override;
};

#endif //STEPIC_SHAPE_H
