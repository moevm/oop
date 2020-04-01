#include "gamewindow.h"

Game<TwoPlayersRule>* Game<TwoPlayersRule>::instance = 0;
template<typename T>
Game<T>* Game<T>::instance = 0;


GameWindow::GameWindow(QWidget *parent) : QWidget(parent)
{
    resize(1700, 1000);
    game = Game<TwoPlayersRule>::getInstance();
    soloGame = Game<SingleGameRule>::getInstance();

    paintWidget = new PaintWidget;
    buttonCreate = new QPushButton;
    buttonCreate->setText("Create");
    hLayout = new QHBoxLayout;
    vLayout = new QVBoxLayout;
    unitLabel = new QLabel;
    unitLabel->setText("Unit line: ");
    towerLabel = new QLabel;
    towerLabel->setText("Tower line: ");
    typeLabel = new QLabel;
    typeLabel->setText("Unit type: ");
    unitBox = new QSpinBox;
    unitBox->setRange(1, 8);
    unitBox->setValue(1);
    towerBox = new QSpinBox;
    towerBox->setRange(1, 8);
    towerBox->setValue(1);
    typeBox = new QComboBox;
    typeBox->addItem("BitingZomby");
    typeBox->addItem("StinkyZomby");
    typeBox->addItem("StrongZomby");
    typeBox->addItem("KamikadzeZomby");
    typeBox->addItem("SpitToEnemyZomby");
    typeBox->addItem("SpitToAreaZomby");
    typeBox->addItem("HumanWithBat");
    typeBox->addItem("HumanWithSword");
    typeBox->addItem("HumanWithGun");
    typeBox->addItem("HumanWithGrenade");
    typeBox->addItem("HumanOnCar");
    typeBox->addItem("humanOnBike");
    unitLineLayout = new QHBoxLayout;
    towerLineLayout = new QHBoxLayout;
    unitTypeLayout = new QHBoxLayout;
    endStepButton = new QPushButton;
    endStepButton->setText("End step");
    stateLabel = new QLabel;
    stateLabel->setText("Zombyes' step");
    stateLabel->setFixedSize(150, 50);
    topLaypout = new QHBoxLayout;
    buttonNewGame = new QPushButton;
    buttonNewGame->setText("New game");
    buttonSaveGame = new QPushButton;
    buttonSaveGame->setText("Save game");

    hLayout->addWidget(paintWidget);
    topLaypout->addWidget(buttonNewGame);
    topLaypout->addWidget(buttonSaveGame);
    vLayout->addLayout(topLaypout);
    vLayout->addWidget(stateLabel);
    unitLineLayout->addWidget(unitLabel);
    unitLineLayout->addWidget(unitBox);
    vLayout->addLayout(unitLineLayout);
    towerLineLayout->addWidget(towerLabel);
    towerLineLayout->addWidget(towerBox);
    vLayout->addLayout(towerLineLayout);
    unitTypeLayout->addWidget(typeLabel);
    unitTypeLayout->addWidget(typeBox);
    vLayout->addLayout(unitTypeLayout);
    vLayout->addWidget(buttonCreate);
    vLayout->addWidget(endStepButton);
    hLayout->addLayout(vLayout);
    setLayout(hLayout);

    connect(buttonCreate, SIGNAL(clicked()), this, SLOT(create()));
    connect(endStepButton, SIGNAL(clicked()), this, SLOT(endStep()));
    connect(game->getSignalMaker().get(), SIGNAL(stateChangeSignal(Kind)), this, SLOT(setStepLabel(Kind)));
    connect(soloGame->getSignalMaker().get(), SIGNAL(stateChangeSignal(Kind)), this, SLOT(setStepLabel(Kind)));
    connect(buttonSaveGame, SIGNAL(clicked()), this, SLOT(saveGame()));
    connect(buttonNewGame, SIGNAL(clicked()), this, SLOT(startNewGame()));
}


GameWindow::~GameWindow() {

}


void GameWindow::startNewGame() {
    if(mode == GameMode::TWO_PLAYERS_GAME) {
        game->startNewGame(6, 8);
        paintWidget->setGame(game);
        paintWidget->setMode(mode);
        connect(game->getField().get(), SIGNAL(gameEndSignal()), this, SLOT(gameEnd()));
        game->getField()->printField();
    }
    else {
        soloGame->startNewGame(6, 8);
        paintWidget->setSoloGame(soloGame);
        paintWidget->setMode(mode);
        connect(soloGame->getField().get(), SIGNAL(gameEndSignal()), this, SLOT(gameEnd()));
        soloGame->getField()->printField();
    }
}

void GameWindow::loadGame() {
    Loader loader;
    mode = loader.loadGameMode();
    paintWidget->setMode(mode);
    if (mode == GameMode::SOLO_GAME) {
        soloGame->setStepNumber(loader.loadStepNumber());
        soloGame->setField(loader.loadField());
        soloGame->setStates(loader.loadState());
        paintWidget->setSoloGame(soloGame);
        connect(soloGame->getField().get(), SIGNAL(gameEndSignal()), this, SLOT(gameEnd()));
    }
    else {
        game->setStepNumber(loader.loadStepNumber());
        game->setField(loader.loadField());
        game->setStates(loader.loadState());
        paintWidget->setGame(game);
        connect(game->getField().get(), SIGNAL(gameEndSignal()), this, SLOT(gameEnd()));
    }

}


void GameWindow::create() {
    UnitType type;
    switch (typeBox->currentIndex()) {
    case 0:
        type = UnitType::BITING_ZOMBY;
        break;
    case 1:
        type = UnitType::STINKY_ZOMBY;
        break;
    case 2:
        type = UnitType::STRONG_ZOMBY;
        break;
    case 3:
        type = UnitType::KAMIKADZE_ZOMBY;
        break;
    case 4:
        type = UnitType::SPIT_TO_ENEMY_ZOMBY;
        break;
    case 5:
        type = UnitType::SPIT_TO_AREA_ZOMBY;
        break;

    case 6:
        type = UnitType::HUMAN_WITH_BAT;
        break;
    case 7:
        type = UnitType::HUMAN_WITH_SWORD;
        break;
    case 8:
        type = UnitType::HUMAN_WITH_GUN;
        break;
    case 9:
        type = UnitType::HUMAN_WITH_GRENADE;
        break;
    case 10:
        type = UnitType::HUMAN_ON_CAR;
        break;
    case 11:
        type = UnitType::HUMAN_ON_BIKE;
        break;
    default:
        break;
    }
    if (mode == GameMode::TWO_PLAYERS_GAME) {
        game->create(towerBox->value() - 1, unitBox->value() - 1, type);
    }
    else {
        soloGame->create(towerBox->value() - 1, unitBox->value() - 1, type);
    }
}

void GameWindow::endStep() {
    if (mode == GameMode::TWO_PLAYERS_GAME){
        game->endStep();
    }
    else {
        soloGame->endStep();
    }
}


void GameWindow::gameEnd() {
    std::string res;
    if (mode == GameMode::TWO_PLAYERS_GAME) {
        switch (game->getKind()) {
        case Kind::HUMAN:
            res = "Humans have won!";
            break;
        case Kind::ZOMBY:
            res = "Zombyes have won!";
        }
    }
    else {
        switch (soloGame->getKind()) {
        case Kind::HUMAN:
            res = "Humans have won!";
            break;
        case Kind::ZOMBY:
            res = "Zombyes have won!";
        }
    }
    QMessageBox::information(this, "Game end", res.c_str());
    close();
}


void GameWindow::setStepLabel(Kind kind) {
    switch(kind) {
    case Kind::HUMAN:
        stateLabel->setText("Humans' step");
        break;
    case Kind::ZOMBY:
        stateLabel->setText("Zombyes' step");
    }
}


void GameWindow::setMode(GameMode mode) {
    this->mode = mode;
}


void GameWindow::saveGame() {
    if (mode == GameMode::SOLO_GAME) {
        soloGame->saveGame();
    }
    else {
        game->saveGame();
    }
}
