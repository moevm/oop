#include <iostream>
#include <vector>
#include <chrono>

#include "shape.h"

int main()
{
    Circle example(Coord(1, 1), 3);
    example.SetColor(RGB(14, 68, 145));
   // example.Replace(Coord(3.35,9.1));
   // example.Scale(1.55);
    example.Rotate(PI, Coord(0,0));
    example.PrintInfo();

    Trapezium tr(Coord(-1, 2), Coord(1, 2), Coord(2, 0), Coord(-2, -1));
    tr.Rotate(PI, Coord(-2, -1));
    tr.PrintInfo();

    return 0;
}


