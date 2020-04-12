#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QObject>
#include <QWidget>
#include <QWindow>
#include <QCloseEvent>
#include <QTextEdit>
#include <QLineEdit>
#include <QComboBox >
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QString>
#include <QMessageBox>

#include "InformationHeaders/commandPar.h"
#include "InformationHeaders/unitPar.h"

class GameWindow : public QWidget
{
    Q_OBJECT
public:
    GameWindow();
    virtual void closeEvent(QCloseEvent* event);

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

    // other
    QTextEdit *visualField;

    /*    PAR    */
    size_t gameFieldSize{};
    size_t playersCount{};

signals:
    void gameWindowClosed();
    void createFieldRequest(size_t heigt, size_t width);
    void addBaseRequest(eBaseType baseType, size_t xCoord, size_t yCoord, QString name);
    void addUnitRequest(eUnitsType unitType, QString sourceBaseName);
    void moveUnitRequest(size_t xSource, size_t ySource, size_t xDest, size_t yDist);
    void attackUnitRequest(size_t xSource, size_t ySource, size_t xDest, size_t yDist);
    void cellUnfromationRequest(size_t xCoord, size_t yCoord, eRequest infRequest);

public slots:
    void startNewPlayingWindow(size_t gameFieldSize_, size_t playersCount_);
    void on_addBaseButton_clicked();
    void on_addUnitButton_clicked();
    void on_moveUnitButton_clicked();
    void on_attackUnitButton_clicked();
    void on_cellInfromationButton_clicked();
};

#endif // GAMEWINDOW_H
