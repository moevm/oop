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
    QLabel *unitPositionLabel;
    QSpinBox *xCoordUnitPos;
    QSpinBox *yCoordUnitPos;

    // base
    QPushButton *addBaseButton;
    QLabel *baseTypeLabel;
    QComboBox *baseTypeComboBox;
    QLabel *basePositionLabel;
    QSpinBox *xCoordBasePos;
    QSpinBox *yCoordBasePos;

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

    // other
    QTextEdit *visualField;

    /*    PAR    */
    size_t gameFieldSize{};
    size_t playersCount{};

signals:
    void gameWindowClosed();

public slots:
    void startNewPlayingWindow(size_t gameFieldSize_, size_t playersCount_);
};

#endif // GAMEWINDOW_H
