#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Game/Game.h"


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow), loggingWindow(nullptr) {
    ui->setupUi(this);

    showMaximized();
    ui->graphicsView->showMaximized();

    gameScene = std::make_shared<ModifiedScene>();
    ui->graphicsView->setScene(gameScene.get());


    settings = new QSettings("settings.conf", QSettings::IniFormat);
    loggingDirection = settings->value("settings/loggingDirection", LOGGING_DIR_FILE).toInt();
    loggingMode = settings->value("settings/loggingMode", LOGGING_MODE_DEFAULT).toInt();

    Game& game = Game::getInstance();
    game.getLogAdapter().setLoggingDirection(loggingDirection);
    game.getLogAdapter().setLoggingMode(loggingMode);
    game.initializeByFile("../map.txt");
    game.getGameFacade().setScene(gameScene);
}

MainWindow::~MainWindow() {
    //QSettings settings("settings", QSettings::IniFormat);
    settings->setValue("settings/loggingDirection", loggingDirection);
    settings->setValue("settings/loggingMode", loggingMode);

    delete settings;
    delete ui;
}


void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape)
        ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_buttonEditor_clicked() {
    ui->stackedWidget->setCurrentIndex(1);
    gameScene->updateInterface();
}

void MainWindow::on_buttonClose_clicked() {
    close();
}

void MainWindow::on_loggingButton_clicked() {
    loggingWindow = new LoggingWindow();
    loggingWindow->setLoggingDirection(loggingDirection);
    loggingWindow->setLoggingMode(loggingMode);
    loggingWindow->exec();

    if (loggingWindow->checkAccept()) {
        loggingDirection = loggingWindow->getLoggingDirection();
        loggingMode = loggingWindow->getLoggingMode();

        Game::getInstance().getLogAdapter().setLoggingDirection(loggingDirection);
        Game::getInstance().getLogAdapter().setLoggingMode(loggingMode);
    }

    delete loggingWindow;
    loggingWindow = nullptr;
}
