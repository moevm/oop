#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QLabel>
#include <QSpinBox>
#include <QLayout>
#include <QComboBox>
#include "client_handler.h"



namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow, public IView
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    void askForBasesPosition() override;
    void update() override;
    void setCurrentPlayerInfo(unsigned int currentPlayer) override;
    void showWinnerInfo(unsigned int winnerPlayer) override;

private slots:

    void on_startGameButton_clicked();

    void on_addUnitButton_clicked();

    void on_baseInfoButton_clicked();

    void on_setLoggingTypeButton_clicked();

private:
    Ui::GameWindow *ui;
    GameFacade* facade;

    StartGameHandler* chainOfResponsibilities;
};

#endif // GAMEWINDOW_H
