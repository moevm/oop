#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QObject>
#include <QWidget>
#include <QWindow>
#include <QCloseEvent>
#include <QTextEdit>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QTextCursor>
#include <QMenuBar>
#include <QFileDialog>
#include <QDir>
#include <QTimer>
#include <QTime>

#include "InformationHeaders/commandPar.h"
#include "InformationHeaders/unitPar.h"
#include "InformationHeaders/guiPar.h"
#include "Game/Logging/logfunctionality.h"
#include "Game/GameProcess/GameRules.h"

#define MSEC_TO_SEC_FACTOR 1000
#define UPDATE_INTERVAL 1000

class GameWindow : public QWidget
{
    Q_OBJECT
public:
    GameWindow();
    virtual void closeEvent(QCloseEvent* event);

    friend class Visualizer;

private:
    void setupGameWindow();

    /*    ELEMENTS    */

    // unit
    QPushButton *addUnitButton;
    QLabel *unitTypeLabel;
    QComboBox *unitTypeComboBox;
    QLabel *unitSourceBaseLabel;
    QComboBox *unitSourceBaseComboBox;

    // base
    QPushButton *addBaseButton;
    QLabel *baseTypeLabel;
    QComboBox *baseTypeComboBox;
    QLabel *basePositionLabel;
    QSpinBox *xCoordBasePos;
    QSpinBox *yCoordBasePos;
    QLabel *baseNameLabel;
    QLineEdit *baseNameText;

    // unit functionality
    QPushButton *moveUnitButton;
    QPushButton *attackUnitButton;
    QLabel *unitActionLabel;
    QLabel *unitSourceActionLabel;
    QSpinBox *xCoordUnitSourceAction;
    QSpinBox *yCoordUnitSourceAction;
    QLabel *unitDestActionLabel;
    QSpinBox *xCoordUnitDestAction;
    QSpinBox *yCoordUnitDestAction;

    // logs
    QTextEdit *logs;
    QPushButton *cellInfromationButton;
    QLabel *logCoordsLabel;
    QSpinBox *xCoordLogPos;
    QSpinBox *yCoordLogPos;
    QLabel *cellInfromationWhoLabel;
    QComboBox *cellInfromationWhoComboBox;

    // visualization
    QTextEdit *visualField;
    QLabel *visualFieldLabel;
    QTextEdit *RoadMap;
    QLabel *roadMapLabel;

    // other
    QMenuBar *menuBar;

    // save / load
    QAction *saveMenuBarButton{};
    QAction *loadMenuBarButton{};

    // step switch
    QLabel *currentPlayerLabel;
    QPushButton *passTheMovePushButton;
    QLabel *currentTimeLabel;
    QTimer *timer;
    size_t timeCount{};
    size_t currTimeCount{};
    GAME_RULES_TYPE ruleType;

    /*    PAR    */
    size_t gameFieldSize{};
    size_t playersCount{};

signals:
    void gameWindowClosed();
    void createFieldRequest(size_t heigt, size_t width, GAME_RULES_TYPE type);
    void createLoggerInFacadeRequest(eLOGGER_TYPE type, eLOGGER_OUTPUT_FORMAT format);
    void addBaseRequest(eBaseType baseType, size_t xCoord, size_t yCoord, QString name);
    void addUnitRequest(eUnitsType unitType, QString sourceBaseName);
    void moveUnitRequest(size_t xSource, size_t ySource, size_t xDest, size_t yDist);
    void attackUnitRequest(size_t xSource, size_t ySource, size_t xDest, size_t yDist);
    void cellUnfromationRequest(size_t xCoord, size_t yCoord, eRequest infRequest);
    void saveGameFileRequest(std::string fileName);
    void loadGameFileRequest(std::string fileName);
    void passTheMoveRequest();

public slots:
    void startNewPlayingWindow(size_t gameFieldSize_, size_t playersCount_, int screenWidth, int screenHeight, GAME_RULES_TYPE type);
    void createLoggerRequest(eLOGGER_TYPE type, eLOGGER_OUTPUT_FORMAT format);
    void on_addBaseButton_clicked();
    void on_addUnitButton_clicked();
    void on_moveUnitButton_clicked();
    void on_attackUnitButton_clicked();
    void on_cellInfromationButton_clicked();
    /**
     * @brief handleStatusReport
     * Log on a user screen some info
     * @param level
     * @param tag
     * @param report
     */
    void handleStatusReport(eREPORT_LEVEL level,
                                        const QString& tag,
                                        const QString& report);
    void on_saveButton_clicked();
    void on_loadButton_clicked();
    void restoreBaseName(QString name);
    void on_passTheMove_button_clicked();

    void updateTime();
    void setCurrPlayerNumb(size_t numb);
};

#endif // GAMEWINDOW_H
