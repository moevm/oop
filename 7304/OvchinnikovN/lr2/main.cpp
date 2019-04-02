#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Triangle tmp({50, 50, 50}, 10, 10, 50, 50, 100, 10);
    std::cout << tmp;

    Ellipse tmp1({0, 0, 255}, -100.1, -100.1, 100.1, 300.1);
    std::cout << tmp1;

    RightTriangle tmp2({255, 0, 128}, 100, 100, 50, 120);
    std::cout << tmp2;

    MainWindow w;
    w.show();

    return a.exec();
}
