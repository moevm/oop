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
    connect(this, &UIFacade::reportStatusToGui, window->getGameWindow(), &GameWindow::handleStatusReport);

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

    std::vector<size_t> param{game->getPlayersCount(), game->getField()->getWidth()};
    logger->sendLogInf(USER_LOG, USER_GAME_CREATE, param, SUCCESS);
}

void UIFacade::addBaseRequest(eBaseType baseType, size_t xCoord, size_t yCoord, QString name)
{
    // log request
    std::vector<size_t> param{xCoord, yCoord, static_cast<size_t>(baseType)};
    logger->sendLogInf(USER_LOG, USER_ADD_BASE, param, SUCCESS);

    try {
        game->createBase(baseType, xCoord, yCoord, name);
    } catch (const std::invalid_argument& ex) {
        emit reportStatusToGui(eREPORT_LEVEL::ERROR, "Base name", "Please, enter valid base name");
        logger->sendLogInf(GAME_LOG, GAME_ADD_BASE, param, WRONG, "wrong base name");
        return;
    } catch(const SimpleFieldException& ex) {
        emit reportStatusToGui(eREPORT_LEVEL::WARNING, "Base limit", ex.what());
        logger->sendLogInf(GAME_LOG, GAME_ADD_BASE, param, WRONG, ex.what());
    } catch(const CoordsNotPartOfTheField& ex) {
        emit reportStatusToGui(eREPORT_LEVEL::WARNING, "Field size", ex.what());
        logger->sendLogInf(GAME_LOG, GAME_ADD_BASE, param, WRONG, ex.what());
    }

    emit reportStatusToGui(eREPORT_LEVEL::INFO, "Base adding", "Base was added");
    logger->sendLogInf(GAME_LOG, GAME_ADD_BASE, param, SUCCESS);
}

void UIFacade::addUnitRequest(eUnitsType unitType, QString sourceBaseName)
{
    Coords coords;
    game->getBaseCoordsByName(sourceBaseName, coords);
    std::vector<size_t> coordinates;
    coordinates.push_back(coords.x);
    coordinates.push_back(coords.y);

    // log request
    std::vector<size_t> param{coords.x, coords.y, static_cast<size_t>(unitType)};
    logger->sendLogInf(USER_LOG, USER_ADD_UNIT, param, SUCCESS);

    std::shared_ptr<Command> command = std::make_shared<Command>(ADD_UNIT, coordinates, unitType);
    std::shared_ptr<FacadeMediator> mediator = std::make_shared<addUnitFacadeMediator>(game, command, shared_from_this());;
    command->setMediator(mediator);

    try {
         command->exec();
    } catch (const std::invalid_argument& ex) {
        emit reportStatusToGui(eREPORT_LEVEL::WARNING, "Base existing", ex.what());
        logger->sendLogInf(GAME_LOG, GAME_ADD_UNIT, param, WRONG, ex.what());
        return;
    } catch(const SimpleFieldException& ex) {
        emit reportStatusToGui(eREPORT_LEVEL::WARNING, "Unit limit", ex.what());
        logger->sendLogInf(GAME_LOG, GAME_ADD_UNIT, param, WRONG, ex.what());
        return;
    } catch(const CoordsNotPartOfTheField& ex) {
        emit reportStatusToGui(eREPORT_LEVEL::WARNING, "Field size", ex.what());
        logger->sendLogInf(GAME_LOG, GAME_ADD_UNIT, param, WRONG, ex.what());
        return;
    } catch(const FieldBusyCellException& ex) {
        emit reportStatusToGui(eREPORT_LEVEL::WARNING, "Cell", ex.what());
        logger->sendLogInf(GAME_LOG, GAME_ADD_UNIT, param, WRONG, ex.what());
        return;
    }

    emit reportStatusToGui(eREPORT_LEVEL::INFO, "Unid add", "Success");
    logger->sendLogInf(GAME_LOG, GAME_ADD_UNIT, param, SUCCESS);
}

void UIFacade::moveUnitReguest(size_t xSource, size_t ySource, size_t xDest, size_t yDist)
{
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

    try {
        command->exec();
    } catch (const std::invalid_argument& ex) {
        emit reportStatusToGui(eREPORT_LEVEL::WARNING, "Unit move", ex.what());
        logger->sendLogInf(GAME_LOG, GAME_MOVE_UNIT, param, WRONG, ex.what());
        return;
    } catch(const FieldBusyCellException& ex) {
        emit reportStatusToGui(eREPORT_LEVEL::WARNING, "Cell", ex.what());
        logger->sendLogInf(GAME_LOG, GAME_MOVE_UNIT, param, WRONG, ex.what());
        return;
    } catch(const CoordsNotPartOfTheField& ex) {
        emit reportStatusToGui(eREPORT_LEVEL::WARNING, "Field size", ex.what());
        logger->sendLogInf(GAME_LOG, GAME_MOVE_UNIT, param, WRONG, ex.what());
        return;
    }

    emit reportStatusToGui(eREPORT_LEVEL::INFO, "Unid move", "Success");
    logger->sendLogInf(GAME_LOG, GAME_MOVE_UNIT, param, SUCCESS);
}

void UIFacade::attackUnitRequest(size_t xSource, size_t ySource, size_t xDest, size_t yDist)
{
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

    try {
        command->exec();
    } catch (const std::invalid_argument& ex) {
        emit reportStatusToGui(eREPORT_LEVEL::WARNING, "Unit attack", ex.what());
        logger->sendLogInf(GAME_LOG, GAME_ATTACK_UNIT, param, WRONG, ex.what());
        return;
    } catch(const CoordsNotPartOfTheField& ex) {
        emit reportStatusToGui(eREPORT_LEVEL::WARNING, "Field size", ex.what());
        logger->sendLogInf(GAME_LOG, GAME_ATTACK_UNIT, param, WRONG, ex.what());
        return;
    }

    emit reportStatusToGui(eREPORT_LEVEL::INFO, "Unid attack", "Success");
    logger->sendLogInf(GAME_LOG, GAME_ATTACK_UNIT, param, SUCCESS);
}

void UIFacade::cellInformationReqiest(size_t xCoord, size_t yCoord, eRequest infRequest)
{
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

void UIFacade::receiveStrAnswer([[maybe_unused]] std::string answer)
{
    // TODO: output it to the UI
}

void UIFacade::gameWindowCloseEvent()
{
}
