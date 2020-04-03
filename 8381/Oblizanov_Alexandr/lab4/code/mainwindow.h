#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <uifacade.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, Game *game = nullptr);
    ~MainWindow();

private slots:
    void on_pushAddBase_clicked();
    void on_pushGameInfo_clicked();
    void on_pushBaseInfo_clicked();
    void on_pushAddUnit_clicked();
    void on_pushLandspace_clicked();
    void on_pushMoveUnit_clicked();
    void on_pushItems_clicked();
    void on_pushAddNeutral_clicked();
    void on_pushItemInfo_clicked();
    void on_pushAttack_clicked();

    void on_actionSet_to_file_triggered();

    void on_actionSet_to_terminal_triggered();

    void on_actionSet_disabled_triggered();

    void on_actionSet_short_triggered();

    void on_actionSet_full_triggered();

private:
    Ui::MainWindow *ui;
    UIFacade *facade;
};
#endif // MAINWINDOW_H
