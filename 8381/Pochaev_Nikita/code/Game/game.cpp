#include "game.h"

Game::Game(int argc, char *argv[])
{
    application = new QApplication(argc, argv);
    window = new MainWindow();
}

void Game::start()
{
    guiSetup();
    QApplication::exec();
}

void Game::guiSetup()
{
#ifdef QT_DEBUG
    qDebug() << "Debug: GUI setup of the game started" << endl;
#endif
    // set up full screen view
    QScreen *screen = application->primaryScreen();
    QRect screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();

    /*      MAIN WINDOW     */
    window->resize(static_cast<int>(0.25 * width), static_cast<int>(0.25 * height));
    window->setFixedSize(static_cast<int>(0.25 * width), static_cast<int>(0.25 * height));

    window->show();
#ifdef QT_DEBUG
    qDebug() << "Debug: GUI setup of the game finished" << endl;
#endif
}

void Game::startGameWindow()
{

}
