#pragma once

#include <QDialog>

namespace Ui {
class LoggingWindow;
}

class LoggingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoggingWindow(QWidget *parent = nullptr);
    ~LoggingWindow();

    uint8_t getLoggingDirection();
    uint8_t getLoggingMode();
    void setLoggingDirection(uint8_t);
    void setLoggingMode(uint8_t);
    bool checkAccept();

private slots:
    void on_closeButton_clicked();
    void on_okButton_clicked();

private:
    Ui::LoggingWindow *ui;
    uint8_t loggingDirection;
    uint8_t loggingMode;
    bool accept;
};
