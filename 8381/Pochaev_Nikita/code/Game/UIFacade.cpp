#include "UIFacade.h"
#include "GUI/command.h"

UIFacade::UIFacade(int argc, char *argv[])
{
    application = new QApplication(argc, argv);
    window = std::make_shared<MainWindow>();
}

void UIFacade::start()
{
    guiSetup();

    // CONNECTIONS FOR UI AND BUSINESS LOGIC
    connect(window->getGameWindow(), &GameWindow::createFieldRequest, this, &UIFacade::createFieldRequest);
    connect(window->getGameWindow(), &GameWindow::addBaseRequest, this, &UIFacade::addBaseRequest);
    connect(window->getGameWindow(), &GameWindow::addUnitRequest, this, &UIFacade::addUnitRequest);
    connect(window->getGameWindow(), &GameWindow::moveUnitRequest, this, &UIFacade::moveUnitReguest);
    connect(window->getGameWindow(), &GameWindow::attackUnitRequest, this, &UIFacade::attackUnitRequest);
    connect(window->getGameWindow(), &GameWindow::cellUnfromationRequest, this, &UIFacade::cellInformationReqiest);

    QApplication::exec();
}

QByteArray UIFacade::readStyleSheetFile(const QString &filePath)
{
    QFile inputFile(filePath);
    QByteArray inputData;

    if(inputFile.open(QIODevice::Text | QIODevice::Unbuffered | QIODevice::ReadOnly))
    {
        inputData = inputFile.readAll();
        inputFile.close();
        return inputData;
    }
    else
    {
        return QByteArray();
    }
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

    /*     STYLE SHEET     */
    QString styleSheet = readStyleSheetFile(":/stylesheets/style_sheet.qss");
    application->setStyleSheet(styleSheet);

    window->show();
#ifdef QT_DEBUG
    qDebug() << "Debug: GUI setup of the game finished" << endl;
#endif
}

void UIFacade::createFieldRequest(size_t fieldSize, size_t playersCount)
{
    game = std::make_shared<Game>(fieldSize, fieldSize);
}

void UIFacade::addBaseRequest(eBaseType baseType, size_t xCoord, size_t yCoord, QString name)
{
#ifdef QT_DEBUG
    qDebug() << "Debug: request for base adding accepted in UIFacade" << endl;
#endif
    game->createBase(baseType, xCoord, yCoord, name);
}

void UIFacade::addUnitRequest(eUnitsType unitType, QString sourceBaseName)
{
#ifdef QT_DEBUG
    qDebug() << "Debug: request for unit adding accepted in UIFacade" << endl;
#endif
    Coords coords;
    game->getBaseCoordsByName(sourceBaseName, coords);
    std::vector<size_t> param;
    param.push_back(coords.x);
    param.push_back(coords.y);
    std::shared_ptr<FacadeMediator> mediator;
    std::shared_ptr<Command> command = std::make_shared<Command>(mediator, ADD_UNIT, param, unitType);
    mediator = std::make_shared<addUnitFacadeMediator>(game, command, shared_from_this());
    command->exec();
}

void UIFacade::moveUnitReguest(size_t xSource, size_t ySource, size_t xDest, size_t yDist)
{
#ifdef QT_DEBUG
    qDebug() << "Debug: request for unit move accepted in UIFacade" << endl;
#endif
    std::vector<size_t> param;
    param.push_back(xSource);
    param.push_back(ySource);
    param.push_back(xDest);
    param.push_back(yDist);
    std::shared_ptr<FacadeMediator> mediator;
    std::shared_ptr<Command> command = std::make_shared<Command>(mediator, MOVE_UNIT, param);
    mediator = std::make_shared<unitMoveFacadeMediator>(game, command, shared_from_this());
    command->exec();
}

void UIFacade::attackUnitRequest(size_t xSource, size_t ySource, size_t xDest, size_t yDist)
{
#ifdef QT_DEBUG
    qDebug() << "Debug: request for unit attack accepted in UIFacade" << endl;
#endif
    std::vector<size_t> param;
    param.push_back(xSource);
    param.push_back(ySource);
    param.push_back(xDest);
    param.push_back(yDist);
    std::shared_ptr<FacadeMediator> mediator;
    std::shared_ptr<Command> command = std::make_shared<Command>(mediator, ATTACK_UNIT, param);
    mediator = std::make_shared<unitAttackFacadeMediator>(game, command, shared_from_this());
    command->exec();
}

void UIFacade::cellInformationReqiest(size_t xCoord, size_t yCoord, eRequest infRequest)
{
#ifdef QT_DEBUG
    qDebug() << "Debug: request for cell infromation accepted in UIFacade" << endl;
#endif
    std::vector<size_t> param;
    param.push_back(xCoord);
    param.push_back(yCoord);
    std::shared_ptr<FacadeMediator> mediator;
    std::shared_ptr<Command> command = std::make_shared<Command>(mediator, infRequest, param);
    mediator = std::make_shared<FacadeMediator>(game, command, shared_from_this());
    command->exec();
}

void UIFacade::receiveStrAnswer(std::string answer)
{
    // TODO: output it to the UI
}
