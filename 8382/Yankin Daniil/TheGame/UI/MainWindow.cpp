#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Game/Game.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    showMaximized();
    ui->graphicsView->showMaximized();

    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    sceneEditor = new ModifiedScene;
    ui->graphicsView->setScene(sceneEditor);

    Game& game = Game::getInstance();
    game.initializeByFile("../map.txt");
    game.getGameFacade().setScene(sceneEditor);
}

MainWindow::~MainWindow() {
    delete sceneEditor;
    delete ui;
}

void MainWindow::on_buttonEditor_clicked() {
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_buttonClose_clicked() {
    close();
}
