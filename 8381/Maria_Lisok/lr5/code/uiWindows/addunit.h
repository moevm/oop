#ifndef ADDUNIT_H
#define ADDUNIT_H

#include <QDialog>
#include "mainwindow.h"

class MainWindow;

namespace Ui {
class AddUnit;
}

class AddUnit : public QDialog
{
    friend class MainWindow;
    Q_OBJECT

public:
    explicit AddUnit(QWidget *parent = nullptr);
    ~AddUnit();
    MainWindow* ptr;



private:
    Ui::AddUnit *ui;
};

#endif // ADDUNIT_H
