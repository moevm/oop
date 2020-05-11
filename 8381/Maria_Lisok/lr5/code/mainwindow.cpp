#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_addunit.h"
#include "ui_addneutral.h"
#include "ui_addbase.h"
#include "ui_attack.h"
#include "ui_baseinfo.h"
#include "ui_gameinfo.h"
#include "ui_landinfo.h"
#include "ui_move.h"
#include "ui_neutralinfo.h"
#include "ui_unitinfo.h"

MainWindow::MainWindow(QWidget *parent, Game *game)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    facade = new Facade(ui, game);
    vector<string> neutrals = {"helmet", "mittens", "sabaton", "bandage", "powerpotion", "covid 19", "covid 37", "sword", "hatchet"};
    for(string buf : neutrals)
        ui->typesOfNeutrals->addItem(QString::fromStdString(buf));
    vector<string> units = {"archer", "shaman", "knigth", "rider", "swardman", "ork"};
    for(string buf : units)
        ui->typesOfUnits->addItem(QString::fromStdString(buf));
    string land{};
    for(unsigned i = 0; i < game->getField()->getWidth(); i++){
        for(unsigned j = 0; j < game->getField()->getHeight(); j++){
            land.append(game->getField()->getCell(i,j)->getLandscape()->getLandscapeType()+"\t");
        }
        land += "\n\n";
    }
    ui->fieldWindow->append(QString::fromStdString(land));

}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_gameInfoButton_clicked()
{
    ui->logWindow->clear();
    facade->getGameInfo();
}

void MainWindow::on_addNeutralButton_clicked()
{
    facade->addNeutral(ui->posNeutralX->value(), ui->posNeutralY->value(), ui->typesOfNeutrals->currentIndex()+60);
}

void MainWindow::on_addUnitButton_clicked()
{
    facade->addUnit(ui->baseNum->value(), ui->typesOfUnits->currentIndex()+20);
}

void MainWindow::on_baseInfoButton_clicked()
{
    ui->infoWindow->clear();
    facade->getBaseInfo(ui->baseNum->value());
}

void MainWindow::on_addBaseButton_clicked()
{
    facade->addBase(ui->posBaseX->value(),ui->posBaseY->value(), ui->maxCountOfItems->value(), ui->health->value());
}

void MainWindow::on_moveButton_clicked()
{
    facade->moveUnit(ui->fromX->value(), ui->fromY->value(), ui->stepX->value(), ui->stepY->value());
}

void MainWindow::on_attackButton_clicked()
{
    facade->attackUnit(ui->fromX->value(), ui->fromY->value(), ui->stepX->value(), ui->stepY->value());
}

void MainWindow::on_unitInfoButton_clicked()
{
    ui->infoWindow->clear();
    facade->getUnitInfo(ui->posForInfoX->value(), ui->posForInfoY->value());
}

void MainWindow::on_landInfoButton_clicked()
{
    ui->infoWindow->clear();
    facade->getLandscapeInfo(ui->posForInfoX->value(), ui->posForInfoY->value());
}

void MainWindow::on_neutralInfoButton_clicked()
{
    ui->infoWindow->clear();
    facade->getNeutralInfo(ui->posForInfoX->value(), ui->posForInfoY->value());
}



void MainWindow::on_logToFile_clicked()
{
    facade->setLogger(TOFILE);
}

void MainWindow::on_logToTerminal_clicked()
{
    facade->setLogger(TOTERMINAL);
}

void MainWindow::on_noLogs_clicked()
{
    facade->setLogger(NOLOG);
}


void MainWindow::on_actionsave_game_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open TXT File"),  QDir::homePath(),
            tr("TXT text (*.txt);;All Files (*)"));
    facade->saveGame(fileName.toUtf8().constData());
}

void MainWindow::on_actionload_game_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open TXT File"),  QDir::homePath(),
            tr("TXT text (*.txt);;All Files (*)"));
    facade->loadGame(fileName.toUtf8().constData());
}



void MainWindow::on_actionsettings_logs_triggered()
{

}



void MainWindow::on_actiongame_info_triggered()
{
     GameInfo* gameInfo = new GameInfo(this);
     gameInfo->show();
}

void MainWindow::on_actionadd_neutral_triggered()
{
    AddNeutral* addNeutral = new AddNeutral(this);
    addNeutral->ptr = this;
    vector<string> neutrals = {"helmet", "mittens", "sabaton", "bandage", "powerpotion", "covid 19", "covid 37", "sword", "hatchet"};
    for(string buf : neutrals)
        addNeutral->ui->typesOfNeutrals->addItem(QString::fromStdString(buf));
    addNeutral->show();
}

void MainWindow::on_actionadd_base_triggered()
{
    AddBase* addBase = new AddBase(this);
    addBase->show();
}

void MainWindow::on_actionland_info_triggered()
{
    LandInfo* landInfo = new LandInfo(this);
    landInfo->show();
}

void MainWindow::on_actionneutral_info_triggered()
{
    NeutralInfo* neutralInfo = new NeutralInfo(this);
    neutralInfo->show();
}

void MainWindow::on_actionbase_info_triggered()
{
    BaseInfo* baseInfo = new BaseInfo(this);
    baseInfo->show();
}

void MainWindow::on_actionMove_triggered()
{
    Move *move = new Move(this);
    move->show();
}

void MainWindow::on_actionAttack_triggered()
{
    Attack *attack = new Attack(this);

    attack->show();
}

void MainWindow::on_actionsetting_for_adding_triggered()
{
    AddUnit* addUnit = new AddUnit(this);
    addUnit->ptr = this;
    vector<string> units = {"archer", "shaman", "knigth", "rider", "swardman", "ork"};

    for(string buf : units)
        addUnit->ui->typesOfUnit->addItem(QString::fromStdString(buf));
    addUnit->show();
}

void MainWindow::on_actionInfo_triggered()
{
    UnitInfo* unitInfo = new UnitInfo(this);
    unitInfo->show();
}
