#include <QCoreApplication>
#include <iostream>
#include "color.h"
#include "ellipse.h"
#include "point.h"
#include "regularpentagon.h"
#include "shape.h"
#include "square.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    RegularPentagon regularrentagon(Color(255, 10, 144), Point(50,50), 15);
    cout << regularrentagon << endl;
    regularrentagon.Move(Point(100, 100));
    cout << regularrentagon << endl;
    regularrentagon.Scale(1.1);
    cout << regularrentagon << endl;
    regularrentagon.Rotate(90, 1);
    cout << regularrentagon << endl;
    cout << "END!" << endl;

    return a.exec();
}
