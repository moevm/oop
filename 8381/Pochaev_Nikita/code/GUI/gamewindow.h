#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QObject>
#include <QWidget>
#include <QWindow>
#include <QCloseEvent>
#include <QTextEdit>
#include <QLineEdit>
#include <QFontComboBox>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

class GameWindow : public QWindow
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
    QFontComboBox *unitTypeCompoBox;
    QLabel *unitPositionLabel;
    QSpinBox xCoordUnitPos;
    QSpinBox yCoordUnitPos;

    // base
    QPushButton *addBaseButton;
    QLabel *basePositionLabel;
    QSpinBox xCoordBasePos;
    QSpinBox yCoordBasePos;

    // unit functionality
    QPushButton *moveUnitButton;
    QPushButton *attackUnitButton;
    QPushButton *unitInformationButton;
    QLabel *unitActionLabel;

    // other
    QTextEdit *visualField;
    QTextEdit *logs;

signals:
    void gameWindowClosed();
};

#endif // GAMEWINDOW_H
