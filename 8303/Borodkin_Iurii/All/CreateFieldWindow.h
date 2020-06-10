#ifndef CREATEFIELDWINDOW_H
#define CREATEFIELDWINDOW_H

#include <QDialog>

namespace Ui {
class CreateFieldWindow;
}

enum class Players
{
    PLAYERS_2,
    PLAYERS_3
};

enum class Size
{
    TEN,
    FIFTEEN
};

class CreateFieldWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CreateFieldWindow(QWidget *parent = nullptr);
    ~CreateFieldWindow();

    Players players = Players::PLAYERS_2;
    Size size = Size::TEN;
    bool isAccepted();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    bool ok = false;


    Ui::CreateFieldWindow *ui;
};

#endif // CREATEFIELDWINDOW_H
