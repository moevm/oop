#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "unit.h"
#include "NeutralObj/context.h"
#include "NeutralObj/armor.h"
#include "NeutralObj/medicine.h"
#include "NeutralObj/poison.h"
#include "NeutralObj/weapon.h"

#include "Landscape/forest.h"
#include "Landscape/mountain.h"
#include "Landscape/river.h"
#include "Landscape/proxy.h"


#include "playingfield.h"
#include "iostream"
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
