#include <iostream>

using namespace std;


unsigned long long int current_id = 0;


class Color {
public:
    explicit Color(unsigned r = 255, unsigned g = 255, unsigned b = 255) : red(r % 256), green(g % 256),
                                                                           blue(b % 256) {}

    unsigned getR() const { return red; };

    unsigned getG() const { return blue; };

    unsigned getB() const { return green; };

    Color &operator=(Color const &color) = default;

    friend ostream &operator<<(ostream &out, Color const &color) {
        out << "(" << color.red << "," << color.green << "," << color.blue << ")";
        return out;
    }

private:
    unsigned red, green, blue;
};


class Coord {
public:
    explicit Coord(double x = 0, double y = 0) : x(x), y(y) {}

    double getX() const { return x; }

    double getY() const { return y; }

    Coord &operator=(Coord const &new_coord) = default;

    friend ostream &operator<<(ostream &out, Coord const &coord) {
        out << "(" << coord.x << "," << coord.y << ")";
        return out;
    }

private:
    double x, y;
};


class Shape {
public:
    explicit Shape(Coord p = Coord(0, 0), Color c = Color(255, 255, 255), double a = 0) : position(p), color(c),
                                                                                          angle(a), id(current_id++) {}

    virtual void move(Coord new_position) {
        position = new_position;
    }

    virtual void rotate(double rotation_angle) {
        angle += rotation_angle;
    }

    virtual void setColor(Color new_color) {
        color = new_color;
    }

    virtual Color getColor() {
        return color;
    }

    virtual void scale(double) = 0;

    friend ostream &operator<<(ostream &out, Shape const &shape) {
        cout << "Shape ID: " << shape.id << endl <<
             "Color: " << shape.color << endl <<
             "Position of the center: " << shape.position << endl <<
             "Clockwise rotation angle: " << shape.angle << endl;

        return out;
    }

private:
    Color color;
    Coord position;
    double angle;
    unsigned long long int id;
};

class Parallelogram : public Shape {
public:
    Parallelogram(double w, double h, double wha = 3.141592653, double a = 0, Color c = Color(255, 255, 255),
                  Coord p = Coord(0, 0)) : Shape(p, c, a),
                                           width(w), height(h), wh_angle(wha) {}

    void scale(double factor) override {
        height *= factor;
        width *= factor;
    }

    friend ostream &operator<<(ostream &out, Parallelogram const &parallelogram) {

        cout << dynamic_cast<Shape const &>(parallelogram) << "Shape type: Parallelogram" << endl
             << "Width: " << parallelogram.width << endl <<
             "Height: " << parallelogram.height << endl <<
             "Angle between width and height: " << parallelogram.wh_angle << endl;

        return out;
    }


protected:
    double width, height, wh_angle;
};

class Rectangle : public Shape {
public:

    Rectangle(double w, double h, double a = 0, Color c = Color(255, 255, 255),
              Coord p = Coord(0, 0)) : Shape(p, c, a), width(w), height(h) {}

    void scale(double factor) override {
        height *= factor;
        width *= factor;
    }

    friend ostream &operator<<(ostream &out, Rectangle const &rectangle) {
        cout << dynamic_cast<Shape const &>(rectangle) << "Shape type: Rectangle" << endl <<
             "Width: " << rectangle.width << endl <<
             "Height: " << rectangle.height << endl;

        return out;
    }

protected:
    double width, height;
};

class Hexagram : public Shape {
public:
    explicit Hexagram(double h, double a = 0, Color c = Color(255, 255, 255), Coord p = Coord(0, 0)) : Shape(p, c, a),
                                                                                                       height(h) {}

    void scale(double factor) override {
        height *= factor;
    }

    friend ostream &operator<<(ostream &out, Hexagram const &hexagram) {
        cout << dynamic_cast<Shape const &>(hexagram) << "Shape type: Hexagram" << endl <<
             "The distance between opposing rays: " << hexagram.height << endl;

        return out;
    }

private:
    double height;
};


int main() {
    Hexagram hex(120);
    Rectangle rect(120, 130);
    Parallelogram para(10, 20);

    cout << hex << endl;
    cout << rect << endl;
    cout << para << endl;

    hex.move(Coord(20, 30));
    rect.rotate(100);
    para.scale(1.2);
    rect.setColor(Color(100, 200, 30));

    cout << rect.getColor() << endl << hex.getColor() << endl;

    cout << hex << endl;
    cout << rect << endl;
    cout << para << endl;

    return 0;
}