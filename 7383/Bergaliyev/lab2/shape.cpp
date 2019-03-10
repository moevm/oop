#include "shape.hpp"

unsigned int Shape::count = 1;

std::ostream & operator<<(std::ostream & ostream, Point const & p){
    
    return ostream << "(" << (std::abs(p.x) < eps ? 0 : p.x) << ", " << (std::abs(p.y) < eps ? 0 : p.y) << ") ";
}

std::ostream & operator<<(std::ostream & ostream, Color const & color){
    return ostream << "R=" << (int)color.red << " G=" << (int)color.green << " B=" << (int)color.blue;
}

std::ostream & operator<<(std::ostream & ostream, Shape const & shape) {
    return shape.print(ostream);
}
