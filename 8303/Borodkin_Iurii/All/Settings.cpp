#include "Settings.h"
#include "ui_Settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
}

Settings::~Settings()
{
    delete ui;
}

bool Settings::isAccepted()
{
    return ok;
}

QString Settings::getPath()
{
    return path;
}

QTextBrowser* Settings::getTerminal()
{
    return ui->terminal;
}

TypeLog Settings::typeLog()
{
    return type;
}

TypeOutput Settings::typeOutput()
{
    return tpOutput;
}

void Settings::on_buttonBox_accepted()
{
    ok = true;

    if (ui->terminal_log->isChecked()) {
        type = TypeLog::TERMINAL;
    } else if (ui->file_log->isChecked()) {
        type = TypeLog::FILE;
        path = QFileDialog::getOpenFileName(this, tr("Открыть файл для логирования"), "C:/Users/User/Desktop", "*.log");
    } else {
        type = TypeLog::NOTHING;
    }

    if (ui->nonCounter->isChecked()) {
        tpOutput = TypeOutput::COUNTLESS;
    } else if (ui->counter->isChecked()) {
        tpOutput = TypeOutput::COUNTABLE;
    }

    close();
}

void Settings::on_buttonBox_rejected()
{
    ok = false;
    close();
}
