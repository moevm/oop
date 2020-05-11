#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "facade.h"
#include <uiWindows/addbase.h>
#include <uiWindows/addneutral.h>
#include <uiWindows/baseinfo.h>
#include <uiWindows/gameinfo.h>
#include <uiWindows/landinfo.h>
#include <uiWindows/neutralinfo.h>
#include <uiWindows/move.h>
#include <uiWindows/attack.h>
#include "uiWindows/AddUnit.h"
#include <uiWindows/unitinfo.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class AddUnit;
class AddNeutral;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, Game* game = nullptr);
    ~MainWindow();

   friend class AddUnit;
   friend class AddNeutral;
private slots:
    void on_gameInfoButton_clicked();

    void on_addNeutralButton_clicked();

    void on_addUnitButton_clicked();

    void on_baseInfoButton_clicked();

    void on_addBaseButton_clicked();

    void on_moveButton_clicked();

    void on_attackButton_clicked();

    void on_unitInfoButton_clicked();

    void on_landInfoButton_clicked();

    void on_neutralInfoButton_clicked();

    void on_logToFile_clicked();

    void on_logToTerminal_clicked();

    void on_noLogs_clicked();

    void on_actionsave_game_triggered();

    void on_actionload_game_triggered();

    void on_actionsettings_logs_triggered();

    void on_actiongame_info_triggered();

    void on_actionadd_neutral_triggered();

    void on_actionadd_base_triggered();

    void on_actionland_info_triggered();

    void on_actionneutral_info_triggered();

    void on_actionbase_info_triggered();

    void on_actionMove_triggered();

    void on_actionAttack_triggered();

    void on_actionsetting_for_adding_triggered();

    void on_actionInfo_triggered();

private:
    Ui::MainWindow *ui;
    Facade *facade;
};
#endif // MAINWINDOW_H
