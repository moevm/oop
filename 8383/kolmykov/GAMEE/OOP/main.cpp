#include "Demo.h"
#include <Windows.h>
#include <QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
