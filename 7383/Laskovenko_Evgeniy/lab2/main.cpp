#include <math.h>
#include "shape.h"
#include "circle.h"
#include "ellipse.h"
#include "ellipse_sector.h"

using namespace std;

int main()
{
    cout << "============================================\n";
    cout << "Checking class Circle:\n\n";
    Circle crl(5, {0,0});
    cout << "Creating circle:\n" << crl << endl;
    crl.move({1,1});
    crl.scale(5);
    crl.set_color(RED);
    cout << "Moving, scaling and setting RED color:\n" << crl << endl;

    cout << "============================================\n";
    cout << "Checking class Ellipse:\n\n";
    Ellipse el(4, 2, {0,0});
    cout << "Creating ellipse:\n" << el << endl;
    el.move({1,1});
    el.scale(2);
    el.set_color(WHITE);
    cout << "Moving, scaling and setting WHITE color:\n" << el << endl;
    el.rotate(M_PI/2);
    cout << "Rotating:\n" << el << endl;

    cout << "============================================\n";
    cout << "Checking class Ellipse_sector:\n\n";
    Ellipse_Sector el_sec({2, M_PI/2}, {3, 0}, {0,0});
    cout << "Creating ellipse sector:\n" << el_sec << endl;
    el_sec.move({1,1});
    el_sec.scale(2);
    el_sec.set_color(BLACK);
    cout << "Moving, scaling and setting BLACK color:\n" << el_sec << endl;
    el_sec.rotate(M_PI/2);
    cout << "Rotating:\n" << el_sec << endl;

    cout << "============================================\n";
    cout << "Creating array of base class pointers, point them on every class and rotating:\n\n";
    Shape* sh_arr[3];
    sh_arr[0] = new Circle(2, {0,0});
    cout << "Creating circle:\n" << dynamic_cast<const Circle&>(*(sh_arr[0])) << endl;
    sh_arr[0]->rotate(M_PI/2);
    cout << "Rotating:\n" << dynamic_cast<const Circle&>(*(sh_arr[0])) << endl;
    sh_arr[1] = new Ellipse(6, 4, {0,0});
    cout << "Creating ellipse:\n" << dynamic_cast<const Ellipse&>(*(sh_arr[1])) << endl;
    sh_arr[1]->rotate(M_PI/2);
    cout << "Rotating:\n" << dynamic_cast<const Ellipse&>(*(sh_arr[1])) << endl;
    sh_arr[2] = new Ellipse_Sector({4, M_PI/2}, {2, 0}, {0,0});
    cout << "Creating ellipse sector:\n" << dynamic_cast<const Ellipse_Sector&>(*(sh_arr[2])) << endl;
    sh_arr[2]->rotate(M_PI/2);
    cout << "Rotating:\n" << dynamic_cast<const Ellipse_Sector&>(*(sh_arr[2])) << endl;

    cout << "============================================\n";

    return 0;
}
