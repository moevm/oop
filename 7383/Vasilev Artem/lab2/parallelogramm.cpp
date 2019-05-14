#include "parallelogramm.h"

Parallelogramm::Parallelogramm()
{}

Parallelogramm::Parallelogramm(Point& center, Point& p1, Point& p2, Point& p3, Point& p4)
    : p1(p1), p2(p2), p3(p3), p4(p4), center(center)
{
    a = p1.length(p2);
    b = p2.length(p3);
    c = p3.length(p4);
    d = p4.length(p1);
    if (a != c || b != d)
    {
        std::cout << "ERROR";
        exit(0);
    }
}


Parallelogramm::Parallelogramm(Color& color) : Shape(color)
{}

void Parallelogramm::scale(double coefficient)
{
    this->coefficient = coefficient;
    this->p1.x *= coefficient;
    this->p1.y *= coefficient;
    this->p2.x *= coefficient;
    this->p2.y *= coefficient;
    this->p3.x *= coefficient;
    this->p3.y *= coefficient;
    this->p4.x *= coefficient;
    this->p4.y *= coefficient;
    a *= coefficient;
    b *= coefficient;
    c *= coefficient;
    d *= coefficient;
}

void Parallelogramm::rotate(double angle)
{
    p1.rotate(angle);
    p2.rotate(angle);
    p3.rotate(angle);
    p4.rotate(angle);
}

void Parallelogramm::move(const Point& center) {
    double old_center_coordinate_x = this->center.x;
    double old_center_coordinate_y = this->center.y;
    this->p1.x = this->p1.x + center.x - old_center_coordinate_x;
    this->p1.y = this->p1.y + center.y - old_center_coordinate_y;
    this->p2.x = this->p2.x + center.x - old_center_coordinate_x;
    this->p2.y = this->p2.y + center.y - old_center_coordinate_y;
    this->p3.x = this->p3.x + center.x - old_center_coordinate_x;
    this->p3.y = this->p3.y + center.y - old_center_coordinate_y;
    this->p4.x = this->p4.x + center.x - old_center_coordinate_x;
    this->p4.y = this->p4.y + center.y - old_center_coordinate_y;
    this->center.x = center.x;
    this->center.y = center.y;
}

std::ostream& operator << (std::ostream &print, Parallelogramm& parallelogramm) {
        print << "Координаты центра: О(" << parallelogramm.center.x << ", " << parallelogramm.center.y
              << ")\nКоординаты вершин: P1(" << parallelogramm.p1.x << ", " << parallelogramm.p1.y << "), "
              << "P2(" << parallelogramm.p2.x << ", " << parallelogramm.p2.y << "), " << "P3(" << parallelogramm.p3.x << ", "
              << parallelogramm.p3.y << "), " << "P4(" << parallelogramm.p4.x << ", " << parallelogramm.p4.y << ")"
              << std::endl << "Длины сторон параллелограмма: a = "
              << parallelogramm.a << ", b = " << parallelogramm.b << ", c = " << parallelogramm.c << ", d = " << parallelogramm.d
              << std::endl << "Текущий ID: " << parallelogramm.global_id << std::endl
              << "Текущий цвет: (" << parallelogramm.color.red << ", " << parallelogramm.color.green << ", "
              << parallelogramm.color.blue << ")" << std::endl;
        return print;
}

