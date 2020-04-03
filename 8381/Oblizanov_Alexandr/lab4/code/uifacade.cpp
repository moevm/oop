#include "uifacade.h"

UIFacade::UIFacade(Ui::MainWindow *ui, Game *game)
    : ui(ui), game(game) {
    logger = new LogAdapter(new ProxyLogger(TO_FILE));
    logger->setType(FULL);
    GameCommand gCom(this, game, GAME_INFO, std::vector<int>(), logger);
    logger->pushLog(GAME_CREATE, gCom.exec());
    // RANDOM LAND
    unsigned width = game->getField()->getWidth();
    unsigned height = game->getField()->getHeight();
    for (unsigned i=0; i<width; i++)
    {
        for (unsigned j=0; j<height; j++)
        {
            if ((i+j)%3 != 0)
                game->getField()->addLandscape(i, j, new ProxyLandscape(static_cast<LandType>((i*2+j*3)%5)));
        }
    }
}

bool UIFacade::getGameInfo()
{
    logger->pushLog(USER_GAME_INFO);
    GameCommand gCom(this, game, GAME_INFO, std::vector<int>(), logger);
    std::vector<int> answer = gCom.exec();
    std::string output;
    output += "Field:\nWidth: " + std::to_string(answer[0]) + "\nHeight: " + std::to_string(answer[1]);
    output += "\nItem counter: " + std::to_string(answer[2]) + "\nItem limit: " + std::to_string(answer[3]);
    output += "\nBases number: " + std::to_string(answer[4]);
    ui->textOutput->append(QString::fromStdString(output));
    return true;
}

bool UIFacade::getBaseInfo(int number)
{
    logger->pushLog(USER_BASE_INFO);
    std::vector<std::string> typesName = {"ATT_SC", "ATT_BS", "SUP_SC", "SUP_BS", "SIM_SC", "SIM_BS"};
    std::vector<int> request = {number};
    GameCommand gCom(this, game, BASE_INFO, request, logger);
    std::vector<int> answer = gCom.exec();
    std::string output = "BASE:\nCoords: " + std::to_string(answer[0]) + " " + std::to_string(answer[1]) + "\nStability: " + std::to_string(answer[2]);
    output += "\nUnit Counter: " + std::to_string(answer[3]) + "\nUnit Limit: " + std::to_string(answer[4]);
    output += "\nUnits:\n";
    for (unsigned i=5; i<answer.size(); i++)
    {
        output += typesName[static_cast<unsigned>(answer[i])] + " ";
    }
    ui->textOutput->append(QString::fromStdString(output));
    return true;
}

bool UIFacade::getLandspaceInfo()
{
    logger->pushLog(USER_LAND_INFO);
    ui->textField->clear();
    GameCommand gCom(this, game, LAND_INFO, std::vector<int>(), logger);
    std::vector<int> answer = gCom.exec();
    std::vector<std::string> landsName = {"OPEN  |", "OPEN_B|", "VPN   |", "VPN_B |", "FAST  |", "FAST_B|"};
    unsigned width = static_cast<unsigned>(answer[0]);
    unsigned height = static_cast<unsigned>(answer[1]);
    std::string output;
    for (unsigned i=0; i<height; i++)
    {
        for (unsigned j=0; j<width; j++)
        {
            output += landsName[static_cast<unsigned>(answer[2+(j*height)+i])];
        }
        output += "\n";
    }
    ui->textField->append(QString::fromStdString(output));
    return true;
}

bool UIFacade::getItemsInfo()
{
    GameCommand gCom(this, game, ITEMS_INFO, std::vector<int>(), logger);
    std::vector<std::string> itemsName = {"ATT_SC|", "ATT_BS|", "SUP_SC|", "SUP_BS|", "SIM_SC|", "SIM_BS|", "BASE  |", "CHEST |", "KEYGEN|", "ANTIVR|", "DATA  |", "      |"};
    std::vector<int> answer = gCom.exec();
    unsigned width = static_cast<unsigned>(answer[0]);
    unsigned height = static_cast<unsigned>(answer[1]);
    std::string output;
    for (unsigned i=0; i<height; i++)
    {
        for (unsigned j=0; j<width; j++)
        {
            output += itemsName[static_cast<unsigned>(answer[2+(j*height)+i])];
        }
        output += "\n";
    }
    ui->textField->clear();
    ui->textField->append(QString::fromStdString(output));
    return true;
}

bool UIFacade::getItemInfo(int x, int y)
{
    logger->pushLog(USER_ITEM_INFO);
    std::vector<int> request = {x, y};
    std::vector<std::string> itemsName = {"ATT_SC", "ATT_BS", "SUP_SC", "SUP_BS", "SIM_SC", "SIM_BS", "BASE", "CHEST", "KEYGEN", "ANTIVR", "DATA", "NOTHING"};
    GameCommand gCom(this, game, GETXY, request, logger);
    std::string output;
    std::vector<int> answer;
    try {
        answer = gCom.exec();
    } catch (std::logic_error a) {
        output += "Error while getting item info: ";
        output += a.what();
        ui->debugOutput->append(QString::fromStdString(output));
        return false;
    }
    output += "At coords: (" + std::to_string(x) + ", " + std::to_string(y) + ") is set:\n";
    output += itemsName[static_cast<unsigned>(answer[0])] + "\n";
    if (answer[0] == BASE)
    {
        ui->textOutput->append(QString::fromStdString(output));
        getBaseInfo(answer[1]+1);
    }
    else if (answer[0] < BASE)
    {
        output += "Characterictics:\n";
        output += "Power: " + std::to_string(answer[1] + answer[4]) + "\n";
        output += "Move: " + std::to_string(answer[2] + answer[4]) + "\n";
        output += "Spread: " + std::to_string(answer[3] + answer[4]) + "\n";
        output += "Attack skills:\n";
        output += "Power: " + std::to_string(answer[5] + answer[8]) + "\n";
        output += "Move: " + std::to_string(answer[6] + answer[8]) + "\n";
        output += "Spread: " + std::to_string(answer[7] + answer[8]) + "\n";
        output += "Security skills:\n";
        output += "Power: " + std::to_string(answer[9] + answer[12]) + "\n";
        output += "Move: " + std::to_string(answer[10] + answer[12]) + "\n";
        output += "Spread: " + std::to_string(answer[11] + answer[12]) + "\n";
        output += "Base number: " + std::to_string(answer[13]) + "\n";
        ui->textOutput->append(QString::fromStdString(output));
    }
    else
        ui->textOutput->append(QString::fromStdString(output));
    return true;
}

bool UIFacade::moveItem(int x, int y, int xDelta, int yDelta)
{
    logger->pushLog(USER_MOVE);
    std::vector<int> request = {x, y, xDelta, yDelta};
    GameCommand gCom(this, game, MOVE, request, logger);
    std::string output;
    std::vector<int> answer;
    try {
        answer = gCom.exec();
    } catch (std::logic_error a) {
        output += "Error while moving item: ";
        output += a.what();
        ui->debugOutput->append(QString::fromStdString(output));
        return false;
    }
    if (answer.front() == 0)
    {
        output += "Item is not unit (is not movable)";
        return false;
    }
    else
        output += "Item was moved";
    ui->textOutput->append(QString::fromStdString(output));
    ui->setActX->setValue(x + xDelta);
    ui->setActY->setValue(y + yDelta);
    return true;
}

bool UIFacade::attackUnit(int x, int y, int xDelta, int yDelta)
{
    logger->pushLog(USER_ATTACK);
    std::vector<int> request = {x, y, xDelta, yDelta};
    GameCommand gCom(this, game, ATTACK, request, logger);
    std::string output;
    std::vector<int> answer;
    try {
        answer = gCom.exec();
    } catch (std::logic_error a) {
        output += "Error while attacking: ";
        output += a.what();
        ui->debugOutput->append(QString::fromStdString(output));
        return false;
    }
    return true;
}

bool UIFacade::addBase(int x, int y)
{
    logger->pushLog(USER_BASE_ADD);
    std::vector<int> request = {BASE, x, y};
    GameCommand gCom(this, game, ADD, request, logger);
    std::string output;
    std::vector<int> answer;
    try {
        answer = gCom.exec();
    } catch (std::logic_error a) {
        output += "Error while adding base: ";
        output += a.what();
        ui->debugOutput->append(QString::fromStdString(output));
        return false;
    }
    output += "Added base. Now bases: " + std::to_string(answer[0]);
    ui->textOutput->append(QString::fromStdString(output));
    ui->comboBases->addItem(QString::number(answer[0]));
    return true;
}

bool UIFacade::addUnit(int x, int y, int base, int type)
{
    logger->pushLog(USER_UNIT_ADD);
    std::vector<int> request = {type, base, x, y};
    GameCommand gCom(this, game, ADD, request, logger);
    std::string output;
    std::vector<int> answer;
    try {
        answer = gCom.exec();
    } catch (std::logic_error a) {
        output += "Error while adding unit: ";
        output += a.what();
        ui->debugOutput->append(QString::fromStdString(output));
        return false;
    }
    return true;
}

bool UIFacade::addNeutral(int x, int y, int type)
{
    logger->pushLog(USER_NEUTRAL_ADD);
    std::vector<int> request = {type, x, y};
    GameCommand gCom(this, game, ADD, request, logger);
    std::string output;
    std::vector<int> answer;
    try {
        answer = gCom.exec();
    } catch (std::logic_error a) {
        output += "Error while adding neutral: ";
        output += a.what();
        ui->debugOutput->append(QString::fromStdString(output));
        return false;
    }
    return true;
}

void UIFacade::receiveStrAnswer(RequestType type, std::string answer)
{
    ui->debugOutput->append(QString::fromStdString(answer));
}

void UIFacade::setLogger(LoggerType type)
{
    logger->setLogger(new ProxyLogger(type));
}

UIFacade::~UIFacade()
{
    delete logger;
}

LogAdapter *UIFacade::getLogger() const
{
    return logger;
}


UIFacade *FacadeMediator::getFacade() const
{
    return facade;
}
