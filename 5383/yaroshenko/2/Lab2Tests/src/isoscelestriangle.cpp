#include "isoscelestriangle.h"

IsoscelesTriangle::IsoscelesTriangle(const Point2d& vertex, double side, double phi, double angle) :

    Triangle(vertex,
             Point2d(vertex.x - (2 * side * sin(phi / 2) / 2), vertex.y - (side * cos(phi / 2)) ),
             Point2d(vertex.x + 2 * side * sin(phi / 2) / 2, vertex.y - (side * cos(phi / 2)) ) )
{
    rotate(angle);
}

IsoscelesTriangle::IsoscelesTriangle(double random_range)
{
    unsigned long seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine gen(seed);
    std::uniform_real_distribution<double> vertex(-random_range, random_range);
    std::uniform_real_distribution<double> side(0, random_range);
    std::uniform_real_distribution<double> angle(0, 2*M_PI);
    std::uniform_int_distribution<unsigned int> color(0, 255);

    Point2d p(vertex(gen), vertex(gen));
    Color c(color(gen), color(gen), color(gen));

    *this = IsoscelesTriangle(p, side(gen), angle(gen), angle(gen));
    setColor(c);
}


void IsoscelesTriangle::scale(double scale)
{
    h *= scale;

    Triangle::scale(scale);
}

void IsoscelesTriangle::print(std::ostream &os) const
{
    os << "[IsoscelesTriangle]" << std::endl;
    os << "a = " << a << ", b = " << b << ", c = " << c << std::endl;
    os << "height = " << h << std::endl;

    Polygon::print(os);
}
