#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QAction>
#include <QCloseEvent>

#include "GUI/gamewindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;
    virtual void closeEvent(QCloseEvent* event);

private:
    void setUpUI();

    // NEW GAME SETUP
    QPushButton *startNewGameButton;
    QLabel *playersCountLabel;
    QSpinBox *playersCountSpinBox;
    QLabel *fieldSizeLabel;
    QSpinBox *fieldSizeSpinBox;

    // GAME WINDOW
    GameWindow *gameWindow;

    // PAR
    size_t gameFieldSize{};
    size_t playersCount{};

private slots:
    void on_startNewGameButton_clicked();
    void on_gameWindow_closeEvent();

signals:
    void startNewGameWindow(size_t gameFieldSize, size_t playersCount);
};

#endif // MAINWINDOW_H
