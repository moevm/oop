#ifndef UIFACADE_H
#define UIFACADE_H
#include "command.h"
#include "ui_mainwindow.h"

class FacadeMediator;

class UIFacade
{
public:
    UIFacade(Ui::MainWindow *ui, Game *game);
    bool getGameInfo();
    bool getBaseInfo(int number);
    bool getLandspaceInfo();
    bool getItemsInfo();
    bool getItemInfo(int x, int y);
    bool moveItem(int x, int y, int xDelta, int yDelta);
    bool attackUnit(int x, int y, int xDelta, int yDelta);
    bool addBase(int x, int y);
    bool addUnit(int x, int y, int base, int type);
    bool addNeutral(int x, int y, int type);
    void receiveStrAnswer(RequestType type, std::string answer);
    void setLogger(LoggerType type);
    LogAdapter *getLogger() const;
    ~UIFacade();

private:
    Ui::MainWindow *ui;
    Game *game;
    FacadeMediator *gameConnect;
    LogAdapter *logger;
};

class FacadeMediator : public IFacadeMediator {
public:
    FacadeMediator(UIFacade *facade, Command *command)
        : facade(facade), command(command) {}
    void sendString(RequestType type, std::string answer) {
        facade->receiveStrAnswer(type, answer);
    }
    UIFacade *getFacade() const;

private:
    UIFacade *facade;
    Command *command;
};


#endif // UIFACADE_H
