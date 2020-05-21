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
#include <QComboBox>
#include <QCheckBox>

#include "GUI/gamewindow.h"
#include "Game/Logging/logfunctionality.h"
#include "Game/GameProcess/GameRules.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;
    virtual void closeEvent(QCloseEvent* event);
    GameWindow* getGameWindow() const;

private:
    void setUpUI();

    /*  NEW GAME SETUP  */

    QPushButton *startNewGameButton;

    // game setup
    QLabel *gameSetupLabel;
    // custom
    QLabel *playersCountLabel;
    QSpinBox *playersCountSpinBox;
    QLabel *fieldSizeLabel;
    QSpinBox *fieldSizeSpinBox;
    // rules
    QLabel *gameRulesLabel;
    QComboBox *gameRulesComboBox;
    QTextEdit *rulesInformationText;

    // log
    QLabel *logModeLabel;
    QComboBox *logModeComboBox;
    QCheckBox *logAdvancedModeCheckBox;

    // GAME WINDOW
    GameWindow *gameWindow;

    // PAR
    size_t gameFieldSize{};
    size_t playersCount{};

private slots:
    void on_startNewGameButton_clicked();
    void on_gameWindow_closeEvent();
    void on_RuleValue_changed(int index);

signals:
    void startNewGameWindow(size_t gameFieldSize, size_t playersCount, int screenWidth, int screenHeight, GAME_RULES_TYPE type);
    void startLogging(eLOGGER_TYPE type, eLOGGER_OUTPUT_FORMAT format);
};

#endif // MAINWINDOW_H
