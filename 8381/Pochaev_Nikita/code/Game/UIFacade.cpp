#include "UIFacade.h"

UIFacade::UIFacade(int argc, char *argv[])
{
    application = new QApplication(argc, argv);
    window = new MainWindow();
}

void UIFacade::start()
{
    guiSetup();

    // CONNECTIONS FOR UI AND BUSINESS LOGIC
    connect(window, &MainWindow::startNewGameWindow, this, &UIFacade::createFieldRequest);

    QApplication::exec();
}

void UIFacade::guiSetup()
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

UIFacade::~UIFacade()
{
    delete application;
    delete window;
    delete game;
}

void UIFacade::startGameWindow()
{

}

void UIFacade::receiveStrAnswer(Request request, std::string answer)
{
    // TODO: output
}

void UIFacade::createFieldRequest(size_t fieldSize, size_t playersCount)
{
    game = new Game(fieldSize, fieldSize);
}
