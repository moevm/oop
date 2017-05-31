#include "Shapes.h"

int Shape::_last_id = 1;

const bool operator < (const Shape& rv, const Shape& lv) {
    return (rv.radius()<lv.radius());
}