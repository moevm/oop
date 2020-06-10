#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QTextBrowser>
#include <QFileDialog>

namespace Ui {
class Settings;
}

enum class TypeLog
{
    TERMINAL,
    FILE,
    NOTHING
};

enum class TypeOutput
{
    COUNTLESS,
    COUNTABLE
};

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    bool isAccepted();
    TypeLog typeLog();
    TypeOutput typeOutput();
    QString getPath();
    QTextBrowser* getTerminal();
    ~Settings();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    QString path;
    bool ok = false;
    TypeLog type = TypeLog::NOTHING;
    TypeOutput tpOutput = TypeOutput::COUNTLESS;
    Ui::Settings *ui;
};

#endif // SETTINGS_H
