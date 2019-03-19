#include <iostream>

typedef struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;

    Color(unsigned char red = 0, unsigned char green = 0, unsigned char blue = 0) :
        r(red),
        g(green),
        b(blue)
    {
    }

    Color(const Color& item) :
        r(item.r),
        g(item.g),
        b(item.b)
    {
    }

    friend std::ostream& operator<<(std::ostream& stream, const Color& color) {
        stream << '(' << int(color.r) << ',' << int(color.g) << ',' << int(color.b) << ')';
        return stream;
    }

} Color;

class Shape{
public:

    void setCoordinates(double newX, double newY) {
        s_x = newX;
        s_y = newY;
    }

    Shape(double x = 0.0, double y = 0.0, double r_angle = 0.0, const Color& color = Color()) :
        s_x(x),
        s_y(y),
        id (id_counter++),
        s_color(color),
        rotation_angle(r_angle)
    {
    }

    virtual ~Shape() = default;

    void setColor(const Color& newColor)
    {
        s_color = newColor;
    }

    const Color getColor(){
        return s_color;
    }

    void rotate(double angle) {
        rotation_angle += angle;
    }

    virtual void scale(double) = 0;

    friend inline std::ostream& operator<<(std::ostream& stream, Shape& shape) {
        return shape.printShape(stream);
    }

    int get_id(){
        return id;
    }

protected:
    virtual std::ostream& printShape(std::ostream&) = 0;
    double s_x;
    double s_y;
    int id;
    Color s_color;
    double rotation_angle;

private:
    static int id_counter;
};

int Shape::id_counter = 0;

class Sector : public Shape {
public:
    Sector(double x = 0, double y = 0, double r_angle = 0.0, Color color = Color(), double radius = 1.0, double angle = 360.0) :
        Shape(x, y, r_angle, color),
        s_angle(angle),
        s_radius(radius)
    {
    }

    Sector(const Sector& item):
        Shape(item.s_x, item.s_y, item.rotation_angle, item.s_color),
        s_angle(item.s_angle),
        s_radius(item.s_radius)
    {
    }

    Sector& operator=(Sector& item) {
        s_angle = item.s_angle;
        s_color = item.s_color;
        rotation_angle = item.rotation_angle;
        s_radius = item.s_radius;
        s_x = item.s_x;
        s_y = item.s_y;
        return *this;
    }

    void scale(double coefficient) override {
        s_radius *= coefficient;
    }

    ~Sector() override = default;

private:
    std::ostream& printShape(std::ostream& stream = std::cout) override{
        stream << "Сектор круга с углом " << s_angle << " и радиусом " << s_radius << " с центром в координатах (" << this->s_x << ',' << this->s_y << ")" << " и повернут на угол " << this->rotation_angle << " градусов" << ". Цвет - " << this->s_color << " id - " << get_id() << std::endl;
        return stream;
    }

    double s_angle;
    double s_radius;
};


class Star:public Shape{
public:
    Star(double x = 0, double y = 0, double r_angle = 0.0, Color color = Color(), double radius = 1.0) :
        Shape(x, y, r_angle, color),
        s_radius(radius)
        {

    }

    Star(const Star &item):
        Shape(item.s_x, item.s_y, item.rotation_angle, item.s_color),
        s_radius(item.s_radius)
    {
    }

    Star& operator=(Star& item) {
        s_color = item.s_color;
        rotation_angle = item.rotation_angle;
        s_x = item.s_x;
        s_y = item.s_y;
        s_radius = item.s_radius;
        return *this;
    }
    void scale(double coefficient) override{
        s_radius *=coefficient;
    }

    ~Star() override = default;
private:
    std::ostream& printShape(std::ostream& stream = std::cout) override{
        stream << "Звезда радиусом " << s_radius << " с центром в координатах (" << this->s_x << ',' << this->s_y << ")" << " и повернута на угол " << this->rotation_angle << " градусов" << ". Цвет - " << this->s_color << " id - " << get_id() << std::endl;
        return stream;
    }
    double s_radius;
};

class Ellipse : public Shape {
public:
    Ellipse(double x = 0, double y = 0, double r_angle = 0.0, const Color& color = Color(), double a = 1.0, double b = 1.0) :
        Shape(x, y, r_angle, color),
        e_a(a),
        e_b(b)
    {
    }

    Ellipse(const Ellipse& item) :
        Shape(item.s_x, item.s_y, item.rotation_angle, item.s_color),
        e_a(item.e_a),
        e_b(item.e_b)
    {
        rotation_angle = item.rotation_angle;
    }

    Ellipse& operator=(Ellipse& item) {
        e_a = item.e_a;
        e_b = item.e_b;
        rotation_angle = item.rotation_angle;
        s_x = item.s_x;
        s_y = item.s_y;
        return *this;
    }

    void scale(double coefficient) override {
        e_a *= coefficient;
        e_b *= coefficient;
    }

    ~Ellipse() override = default;

private:
    std::ostream& printShape(std::ostream& stream = std::cout) override {
        stream << "Эллипс с параметрами " << e_a << " , " << e_b << " и центром в координатах (" << this->s_x << "," << this->s_y << ")" << " повернут на угол " << this->rotation_angle << " градусов" << ". Цвет - " << this->s_color << " id - " << get_id() << std::endl;
        return stream;
    }

    double e_a;
    double e_b;
};

int main()
{
    Sector a(10, 10, 90, Color(255, 0, 0), 10, 90);
    Sector b;
    b = a;
    b.setCoordinates(50,50);
    b.rotate(45);
    b.scale(0.5);
    b.setColor(Color(0, 0, 0));

    Star s(100, 100, 0, Color(0,0,0), 50);

    Ellipse e(50, 250, 90, Color(0, 255, 0), 10, 10);

    std::cout << a << s << e << b;

    return 0;
}

