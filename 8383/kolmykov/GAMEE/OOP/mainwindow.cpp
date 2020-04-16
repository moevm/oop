#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    buttonNewGame = new QPushButton;
    buttonNewGame->setText("New two players game");
    buttonLoadGame = new QPushButton;
    buttonLoadGame->setText("Load Game");
    buttonNewSoloGame = new QPushButton;
    buttonNewSoloGame->setText("New solo game");
    centralWidget = new QWidget;
    layout = new QVBoxLayout;
    gameWindow = new GameWindow;

    layout->addWidget(buttonNewGame);
    layout->addWidget(buttonNewSoloGame);
    layout->addWidget(buttonLoadGame);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(buttonNewGame, SIGNAL(clicked()), this, SLOT(newGameButtonClicked()));
    connect(buttonLoadGame, SIGNAL(clicked()), this, SLOT(loadGameButtonClicked()));
    connect(buttonNewSoloGame, SIGNAL(clicked()), this, SLOT(soloGameButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete buttonNewGame;
    delete buttonLoadGame;
    delete layout;
    delete centralWidget;
}


void MainWindow::newGameButtonClicked() {
    gameWindow->setMode(GameMode::TWO_PLAYERS_GAME);
    gameWindow->show();
    gameWindow->startNewGame();
    close();
}


void MainWindow::loadGameButtonClicked() {
    gameWindow->show();
    gameWindow->loadGame();
    close();
}


void MainWindow::soloGameButtonClicked() {
    gameWindow->setMode(GameMode::SOLO_GAME);
    gameWindow->show();
    gameWindow->startNewGame();
    close();
}

