#ifndef BASEINFO_H
#define BASEINFO_H

#include <QDialog>
#include "mainwindow.h"

class MainWindow;

namespace Ui {
class BaseInfo;
}

class BaseInfo : public QDialog
{
    friend class MainWindow;
    Q_OBJECT

public:
    explicit BaseInfo(QWidget *parent = nullptr);
    ~BaseInfo();
    MainWindow* ptr;
private:
    Ui::BaseInfo *ui;
};

#endif // BASEINFO_H
