#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <math.h>

using namespace std;

struct point {

    double x;
    double y;
};

enum colors { RED, GREEN, BLUE, YELLOW, NO_COLOR };

class Shape {

    protected:

        vector <point> coordinates;
        point center;
        double angle;
        long int id;
        colors color;

    public:

        Shape(point _center) {

            srand(time(NULL));

            id     = rand();
            color    = NO_COLOR;
            angle  = 0;
            center = _center;
        };

        virtual void scale(double multiplier) = 0;

        void move(point newCenter) {

            center = newCenter;
            makeCoordinates();
        }

        void rotate(double _angle) {

            double _x, _y;

            for (int i = 0; i < coordinates.size(); ++i) {

                _x = coordinates[i].x;
                _y = coordinates[i].y;

                coordinates[i].x = (_x - center.x) * cos(_angle) - (_y - center.y) * sin(_angle) + center.x;
                coordinates[i].y = (_x - center.x) * sin(_angle) + (_y - center.y) * cos(_angle) + center.y;
            }

            angle = _angle;
        }

        colors getColor() {

            return color;
        }

        void setColor(colors _color) {

            color = _color;
        }

        virtual ~Shape() {};

        friend ostream& operator<< (ostream& outputStream, const Shape& shape) {

            outputStream << "Id: " << shape.id << endl;
            outputStream << "Coordinates of extreme points: ";

            for (int i = 0; i < shape.coordinates.size(); ++i) {

                outputStream << "(" << shape.coordinates[i].x << ", " << shape.coordinates[i].y << ") ";
            }

            outputStream << endl << "Color: ";

            switch (shape.color) {

                case RED:
                    outputStream << "red"    << endl;
                    break;

                case GREEN:
                    outputStream << "green"  << endl;
                    break;

                case BLUE:
                    outputStream << "blue"   << endl;
                    break;

                case YELLOW:
                    outputStream << "yellow" << endl;
                    break;

                case NO_COLOR:
            default:
                    outputStream << "color is not defined" << endl;
                    break;
            }

            return outputStream;
        }

    private:

        virtual void makeCoordinates() = 0;
};

/*                           */

class Square : public Shape {

    private:

        double side;

    public:

        Square(double _side, point _center) : Shape (_center) {

            side = _side;
            makeCoordinates();
        }

        void scale(double multiplier) {

            side *= multiplier;
            makeCoordinates();
        }

        ~Square() {

            coordinates.clear();
        }

        friend std::ostream& operator<< (ostream& outputStream, const Square& square) {

            outputStream << "Square" << endl;
            outputStream << (const Shape&)square;
            return outputStream;
        }

    private:

        void makeCoordinates() {

            coordinates.clear();
            coordinates.push_back({ center.x - side / 2, center.y + side / 2 });
            coordinates.push_back({ center.x + side / 2, center.y + side / 2 });
            coordinates.push_back({ center.x + side / 2, center.y - side / 2 });
            coordinates.push_back({ center.x - side / 2, center.y - side / 2 });

            rotate(angle);
        }

};

/*                              */

class Parallelogram : public Shape {

    private:

        double height;
        double lenght;
        double rLenght;

    public:

        Parallelogram(double side, double _side, double _angle, point _center) : Shape (_center) {

            height = side * sin(_angle);
            rLenght = side * cos(_angle);
            lenght = _side - rLenght;

            makeCoordinates();
        }

        void scale(double multiplier) {

            height *= multiplier;
            lenght *= multiplier;
            rLenght *= multiplier;

            makeCoordinates();
        }

        ~Parallelogram() {

            coordinates.clear();
        }

        friend std::ostream& operator<< (ostream& outputStream, const Parallelogram& Pargrm) {

            outputStream << "Parallelogram" << endl;
            outputStream << (const Shape&)Pargrm;

            return outputStream;
        }

    private:

        void makeCoordinates() {

            coordinates.clear();
            coordinates.push_back({ center.x - lenght / 2, center.y + height / 2 });
            coordinates.push_back({ center.x + rLenght + lenght / 2, center.y + height / 2 });
            coordinates.push_back({  center.x + lenght / 2, center.y - height / 2 });
            coordinates.push_back({ center.x - rLenght - lenght / 2, center.y - height / 2 });

            rotate(angle);
        }
};

/*                           */

class Rhombus : public Shape {

    private:
        double side;
        double minDiagonal;
        double maxDiagonal;

    public:

        Rhombus(double _side, double _minDiagonal, double _maxDiagonal, point _center) : Shape(_center) {

            side  = _side;

            if (_minDiagonal < _maxDiagonal) {

                minDiagonal = _minDiagonal;
                maxDiagonal = _maxDiagonal;

            } else {
                maxDiagonal = _minDiagonal;
                minDiagonal = _maxDiagonal;
            }

            makeCoordinates();
        }

        void scale(double multiplier) {

            side 	    *= multiplier;
            maxDiagonal *= multiplier;
            minDiagonal *= multiplier;
            makeCoordinates();
        }

        ~Rhombus() {

            coordinates.clear();
        }

        friend std::ostream& operator<< (ostream& outputStream, const Rhombus& rhombus) {

            outputStream << "Rhombus" << endl;
            outputStream << (const Shape&)rhombus;

            return outputStream;
        }

    private:

        void makeCoordinates() {

            coordinates.clear();
            coordinates.push_back(center);

            coordinates.push_back({ center.x - maxDiagonal / 2, center.y});
            coordinates.push_back({ center.x, center.y + minDiagonal / 2});
            coordinates.push_back({ center.x + maxDiagonal / 2, center.y});
            coordinates.push_back({ center.x, center.y - minDiagonal / 2});

            rotate(angle);
        }
};
