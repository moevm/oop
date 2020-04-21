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
    connect(window->getGameWindow(), &GameWindow::createLoggerInFacadeRequest, this, &UIFacade::createLoggerRequest);
    connect(window->getGameWindow(), &GameWindow::addBaseRequest, this, &UIFacade::addBaseRequest);
    connect(window->getGameWindow(), &GameWindow::addUnitRequest, this, &UIFacade::addUnitRequest);
    connect(window->getGameWindow(), &GameWindow::moveUnitRequest, this, &UIFacade::moveUnitReguest);
    connect(window->getGameWindow(), &GameWindow::attackUnitRequest, this, &UIFacade::attackUnitRequest);
    connect(window->getGameWindow(), &GameWindow::cellUnfromationRequest, this, &UIFacade::cellInformationReqiest);
    connect(window->getGameWindow(), &GameWindow::gameWindowClosed, this, &UIFacade::gameWindowCloseEvent);

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

void UIFacade::createFieldRequest(size_t fieldSize, size_t playersCount_)
{
    game = std::make_shared<Game>(fieldSize, fieldSize, playersCount_);
}

void UIFacade::createLoggerRequest(eLOGGER_TYPE type, eLOGGER_OUTPUT_FORMAT format)
{
    std::shared_ptr<ILogger> loggerProxy = std::make_shared<ProxyLogger>(type);
    logger = std::make_shared<LogAdapter>(loggerProxy);
    logger->setOutputFormat(format);

    // FIXME: (check it) because log creation happens after Facade + Field creation
    std::vector<size_t> param{game->getPlayersCount(), game->getField()->getWidth()};
    logger->sendLogInf(USER_LOG, USER_GAME_CREATE, param);
}

void UIFacade::addBaseRequest(eBaseType baseType, size_t xCoord, size_t yCoord, QString name)
{
#ifdef QT_DEBUG
    qDebug() << "Debug: request for base adding accepted in UIFacade" << endl;
#endif
    // log request
    std::vector<size_t> param{xCoord, yCoord, static_cast<size_t>(baseType)};
    logger->sendLogInf(USER_LOG, USER_ADD_BASE, param);

    game->createBase(baseType, xCoord, yCoord, name);
    // TODO: add check for exceptions
    logger->sendLogInf(GAME_LOG, GAME_ADD_BASE, param);
}

void UIFacade::addUnitRequest(eUnitsType unitType, QString sourceBaseName)
{
#ifdef QT_DEBUG
    qDebug() << "Debug: request for unit adding accepted in UIFacade" << endl;
#endif
    Coords coords;
    game->getBaseCoordsByName(sourceBaseName, coords);
    std::vector<size_t> coordinates;
    coordinates.push_back(coords.x);
    coordinates.push_back(coords.y);

    // log request
    std::vector<size_t> param{coords.x, coords.y, static_cast<size_t>(unitType)};
    logger->sendLogInf(USER_LOG, USER_ADD_UNIT, param);

    std::shared_ptr<Command> command = std::make_shared<Command>(ADD_UNIT, coordinates, unitType);
    std::shared_ptr<FacadeMediator> mediator = std::make_shared<addUnitFacadeMediator>(game, command, shared_from_this());;
    command->setMediator(mediator);

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

    // log request
    logger->sendLogInf(USER_LOG, USER_MOVE_UNIT, param);

    std::shared_ptr<Command> command = std::make_shared<Command>(MOVE_UNIT, param);
    std::shared_ptr<FacadeMediator> mediator = std::make_shared<unitMoveFacadeMediator>(game, command, shared_from_this());
    command->setMediator(mediator);

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

    // log request
    logger->sendLogInf(USER_LOG, USER_ATTACK_UNIT, param);

    std::shared_ptr<Command> command = std::make_shared<Command>(ATTACK_UNIT, param);
    std::shared_ptr<FacadeMediator> mediator = std::make_shared<unitAttackFacadeMediator>(game, command, shared_from_this());
    command->setMediator(mediator);

    command->exec();
}

void UIFacade::cellInformationReqiest(size_t xCoord, size_t yCoord, eRequest infRequest)
{
#ifdef QT_DEBUG
    qDebug() << "Debug: request for cell infromation accepted in UIFacade" << endl;
#endif
    std::vector<size_t> coordinates;
    coordinates.push_back(xCoord);
    coordinates.push_back(yCoord);

    // log request
    std::vector<size_t> param{xCoord, yCoord, static_cast<size_t>(infRequest)};
    logger->sendLogInf(USER_LOG, USER_ATTACK_UNIT, param);

    std::shared_ptr<Command> command = std::make_shared<Command>(infRequest, coordinates);
    std::shared_ptr<FacadeMediator> mediator = std::make_shared<FacadeMediator>(game, command, shared_from_this());
    command->setMediator(mediator);

    command->exec();
}

void UIFacade::receiveStrAnswer(std::string answer)
{
    // TODO: output it to the UI
}

void UIFacade::gameWindowCloseEvent()
{
}
