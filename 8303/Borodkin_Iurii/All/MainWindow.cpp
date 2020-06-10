#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    field = new GameField();
    log.setLogger(new LoggerEmpty);
    log.setTarget(new Target);
    gameField = new MyGraphicsView(*field, &log);
    settings = new Settings(this);
    createFieldWindow = new CreateFieldWindow(this);
    ui->gameField->addWidget(gameField);
    ui->add_unit->hide();
}

MainWindow::~MainWindow()
{
    delete gameField;
    delete field;
    delete createFieldWindow;
    delete ui;
}

void MainWindow::on_create_field_clicked()
{
    log << "Creating field...";
    try {
        if (!gameField->win() && !field->empty())
        {
            throw DoublePlaceFieldException();
        }
    } catch (DoublePlaceFieldException) {
        QMessageBox::warning(this, "Warning", "Поле уже создано!");
        log << "Creating field was failed: Field already created";
        return;
    } catch(...) {
        log << "Unknown error";
        return;
    }

    createFieldWindow->exec();
    if (!createFieldWindow->isAccepted())
    {
        log << "Creating field was failed: User did not click accept";
        return;
    }
    log << "Creating field was succuseful";

    delete game1;
    delete game2;
    delete game3;
    delete game4;

    game1 = nullptr;
    game2 = nullptr;
    game3 = nullptr;
    game4 = nullptr;

    if (createFieldWindow->size == Size::TEN && createFieldWindow->players == Players::PLAYERS_2) {
        game1 = new Game<Rule1, Players2>(field);
        field->countPlayers = 2;
    } else if (createFieldWindow->size == Size::TEN && createFieldWindow->players == Players::PLAYERS_3) {
        game2 = new Game<Rule1, Players3>(field);
        field->countPlayers = 3;
    } else if (createFieldWindow->size == Size::FIFTEEN && createFieldWindow->players == Players::PLAYERS_2) {
        game3 = new Game<Rule2, Players2>(field);
        field->countPlayers = 2;
    } else {
        game4 = new Game<Rule2, Players3>(field);
        field->countPlayers = 3;
    }

    delete gameField;
    gameField = new MyGraphicsView(*field, &log, ui->charsObject, ui->add_unit);

    if (game1) {
        gameField->game1 = game1;
        field->state = game1->getNextState();
    } else if (game2) {
        gameField->game2 = game2;
        field->state = game2->getNextState();
    } else if (game3) {
        gameField->game3 = game3;
        field->state = game3->getNextState();
    } else if (game4) {
        gameField->game4 = game4;
        field->state = game4->getNextState();
    }

    ui->gameField->addWidget(gameField);
}

void MainWindow::on_add_unit_clicked()
{
    log << "User clcik on \"Add unit\"";

    if (field->empty())
    {
        log << "Adding unit failed";
        QMessageBox::warning(this, "Warning", "Создайте поле!");
        return;
    }

    LongRangeFactory lFactory;
    ShortRangeFactory sFactory;
    RiderFactory rFactory;
    std::string str;
    auto coords = gameField->getCoordsToAddUnit();

    if (ui->archer->isChecked()) {
//        field->addUnit
//                (lFactory.createArcher(), coords);
        gameField->inv.createUnitToBase(lFactory.createArcher(), coords);
        str = "Archer";
    } else if (ui->wizard->isChecked()) {
//        field->addUnit
//                (lFactory.createWizard(), coords);
        gameField->inv.createUnitToBase(lFactory.createWizard(), coords);
        str = "Wizard";
    } else if (ui->swordsman->isChecked()) {
//        field->addUnit
//                (sFactory.createSwordsMan(), coords);
        gameField->inv.createUnitToBase(sFactory.createSwordsMan(), coords);
        str = "SwordsMan";
    } else if (ui->spearman->isChecked()) {
//        field->addUnit
//                (sFactory.createSpearMan(), coords);
        gameField->inv.createUnitToBase(sFactory.createSpearMan(), coords);
        str = "SpearMan";
    } else if (ui->panzer->isChecked()) {
//        field->addUnit
//                (rFactory.createPanzer(), coords);
        gameField->inv.createUnitToBase(rFactory.createPanzer(), coords);
        str = "Panzer";
    } else if (ui->centaur->isChecked()) {
//        field->addUnit
//                (rFactory.createCentaur(), coords);
        gameField->inv.createUnitToBase(rFactory.createCentaur(), coords);
        str = "Centaur";
    }

    log << str + " added succesful";

    gameField->update();


    MonitorBase mBase;
    Reflector ref;

    QString qstr = "Base\n";
    qstr.append("Hp: " + QString::number(dynamic_cast<Base*>(field->at(coords).obj)->health()) + "\nUnits:\n");
    mBase.addObserver(ref);
    mBase.resetBase(*dynamic_cast<Base*>(field->at(coords).obj), &qstr);
    ui->charsObject->append(qstr);
}

void MainWindow::on_actionSettings_triggered()
{
    settings->exec();

    if (!settings->isAccepted())
        return;

    switch (settings->typeLog())
    {
        case TypeLog::FILE:
        {
            log.setLogger(new LoggerFile(settings->getPath().toStdString()));
            break;
        }
        case TypeLog::TERMINAL:
        {
            log.setLogger(new LoggerTerminal(settings->getTerminal()));
            break;
        }
        default:
        {
            log.setLogger(new LoggerEmpty);
            break;
        }
    }

    switch (settings->typeOutput())
    {
        case TypeOutput::COUNTABLE:
        {
            log.setTarget(new Adapter);
            break;
        }

        case TypeOutput::COUNTLESS:
        {
            log.setTarget(new Target);
            break;
        }
    }

}

void MainWindow::on_undoAction_triggered()
{
    log << "User press button \"undo\"";
    if (field->empty())
    {
        QMessageBox::warning(this, "Warning", "Создайте поле!");
        return;
    }

    gameField->onUndoClicked = true;
    gameField->inv.undo();
    gameField->update();
}

void MainWindow::on_actionSave_triggered()
{
    log << "User press button \"Save game\"";
    auto path = QFileDialog::getOpenFileName(this, tr("Открыть файл для сохранения состояния игры"), "C:/Users/User/Desktop", tr("*.save")).toStdString();
    try {
        GameSaveLoad state(path, gameField->saveState());
        state.save();
    } catch (InvalidFielLoadingException) {

        log << "file wasnt open";
        QMessageBox::warning(this, "Warning", "Файл не был открыт");
        return;

    } catch(...) {
        log << "unknown error";
        QMessageBox::warning(this, "Warning", "Неизвестная ошибка!");
        return;
    }
}

void MainWindow::on_actionLoad_triggered()
{
    log << "User press button \"Load game\"";

    auto path = QFileDialog::getOpenFileName(this, tr("Открыть файл для сохранения состояния игры"), "C:/Users/User/Desktop", tr("*.save")).toStdString();
    if (path.empty())
    {
        log << "User cancel \"Load game\"";
        return;
    }
    GameSaveLoad state(path, gameField->saveState());

    log << "Loading game...";
    auto res = state.load();

    if (res.second) {

        log << "Load game completed succesful";
        delete field;
        field = res.first.getState();
        game1 = res.first.game1;
        game2 = res.first.game3;
        game3 = res.first.game2;
        game4 = res.first.game4;
        delete gameField;

        if (game1) {
            gameField->game1 = game1;
            field->state = game1->getNextState();
        } else if (game2) {
            gameField->game2 = game2;
            field->state = game2->getNextState();
        } else if (game3) {
            gameField->game3 = game3;
            field->state = game3->getNextState();
        } else if (game4) {
            gameField->game4 = game4;
            field->state = game4->getNextState();
        }

        gameField = new MyGraphicsView(*field, &log,  ui->charsObject, ui->add_unit);
        ui->gameField->addWidget(gameField);
        gameField->update();

    } else {

        log << "Invalid save file";
        QMessageBox::warning(this, "Warning", "Invalid save file");
        return;

    }
}
