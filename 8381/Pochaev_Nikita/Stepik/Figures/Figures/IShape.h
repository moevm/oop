/**
 * 1. перемещения в указанные координаты
 * 2. поворот на заданный угол
 * 3. масштабирования на заданный коэффициент
 * 4. установка и получения цвета
 * 5. оператор вывода в поток
 */

#ifndef STEPIC_ISHAPE_H
#define STEPIC_ISHAPE_H

#include <memory>

#include "BasePoint.h"
#include "../Subsidiary/ANSIColor.h"

class IShape {
public:
    virtual ~IShape() = default;

    // Center stuff
    virtual std::shared_ptr<BasePoint> getCenter() = 0;
    virtual void calcCenter() = 0;

    // Main task functions
    virtual void move(std::vector<BasePoint> newVertex) = 0;
    virtual void rotate(float angle) = 0;   // angle in rad
    virtual void scale(float factor) = 0;
    virtual void setColor(ANSIColor::eCOLOR_CODE color) = 0;
    virtual std::string getColor() = 0;
};

#endif //STEPIC_ISHAPE_H
