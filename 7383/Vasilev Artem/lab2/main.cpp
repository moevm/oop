#include <iostream>
#include <math.h>

#include "triangle.h"
#include "righttriangle.h"
#include "parallelogramm.h"



int main()
{
    Point point1(2, 2);
    Point point2(5, 7);
    Point point3(6, 1);
    Point center((point1.x+point2.x+point3.x)/3, (point1.y+point2.y+point3.y)/3);
    Triangle t_1(center, point1, point2, point3);
    std::cout << "Параметры треугольника после объявления:" << std::endl << t_1 << std::endl;
    t_1.move(point2);
    t_1.setColor(Color(255, 255, 255));
    std::cout << "Параметры треугольника после перемещения центра и изменения цвета:" << std::endl << t_1 << std::endl;
    t_1.rotate(90);
    std::cout << "Параметры треугольника после поворота:" << std::endl << t_1 << std::endl;
    t_1.scale(1.5);
    t_1.setColor(Color(0, 0, 0));
    std::cout << "Параметры треугольника после масштабирования и изменения цвета:" << std::endl << t_1 <<std::endl;
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    Point center1(4, 4);
    Point p1(1, 2), p2(5, 2), p3(7, 6), p4(3, 6);
    Parallelogramm p_1(center1, p1, p2, p3, p4);
    p_1.setColor(Color(122, 240, 99));
    std::cout << "Параметры параллелограмма после объявления:" << std::endl << p_1 << std::endl;
    p_1.move(p2);
    std::cout << "Параметры параллелограмма после перемещения центра:" << std::endl  << p_1 << std::endl;
    p_1.rotate(90);
    std::cout << "Параметры параллелограмма после поворота:" << std::endl  << p_1 << std::endl;
    p_1.scale(1.5);
    p_1.setColor(Color(0, 0, 0));
    std::cout << "Параметры параллелограмма после масштабирования и изменения цвета:" << std::endl  << p_1 << std::endl;
    std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
    Point pointR1(0, 0);
    Point pointR2(1/2, sqrt(3/2));
    Point pointR3(1, 0);
    /*Point pointR1(1, 1);
    Point pointR2(4, 6);
    Point pointR3(7, 1);*/
    Point centerR((pointR1.x+pointR2.x+pointR3.x)/3, (pointR1.y+pointR2.y+pointR3.y)/3);
    rightTriangle RT_1(centerR, pointR1, pointR2, pointR3);
    std::cout << "Параметры правильного треугольника после объявления:" << std::endl << RT_1 << std::endl;
    RT_1.move(pointR2);
    RT_1.setColor(Color(13, 45, 129));
    std::cout << "Параметры правильного треугольника после перемещения центра и изменения цвета:" << std::endl  << RT_1 << std::endl;
    RT_1.rotate(270);
    std::cout << "Параметры правильного треугольника после поворота:" << std::endl  << RT_1 << std::endl;
    RT_1.scale(2.0);
    RT_1.setColor(Color(12, 12, 12));
    std::cout << "Параметры правильного треугольника после масштабирования и изменения цвета:" << std::endl  << RT_1 << std::endl;
}



