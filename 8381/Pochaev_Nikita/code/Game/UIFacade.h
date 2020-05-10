#ifndef UIFACADE_H
#define UIFACADE_H

#include <QApplication>
#include <QScreen>
#include <QDebug>

#include "GUI/mainwindow.h"
#include "InformationHeaders/commandPar.h"
#include "game.h"
#include "GameField/Coords.h"

#include "Game/Logging/Loggers/ILogAdapter.h"
#include "Game/Logging/Loggers/loggers.h"
#include "Game/Logging/Loggers/logadapter.h"

class UIFacade : public QObject, public std::enable_shared_from_this<UIFacade>
{
    Q_OBJECT

public:
    UIFacade(int argc, char *argv[]);
    ~UIFacade() = default;

    void start();
    void receiveStrAnswer(std::string answer);

private:
    QApplication *application;
    // GUI
    std::shared_ptr<MainWindow> window;
    // Game
    std::shared_ptr<Game> game;
    // Logger
    std::shared_ptr<ILogAdapter> logger;
    eLOGGER_OUTPUT_FORMAT loggerFormat;

    // Window show preparation
    void guiSetup();
    [[nodiscard]] QByteArray readStyleSheetFile(const QString &filePath);

public slots:
    void createFieldRequest(size_t fieldSize, size_t playersCount);
    void createLoggerRequest(eLOGGER_TYPE type, eLOGGER_OUTPUT_FORMAT format);
    void addBaseRequest(eBaseType baseType, size_t xCoord, size_t yCoord, QString name);
    void addUnitRequest(eUnitsType unitType, QString sourceBaseName);
    void moveUnitReguest(size_t xSource, size_t ySource, size_t xDest, size_t yDist);
    void attackUnitRequest(size_t xSource, size_t ySource, size_t xDest, size_t yDist);
    void cellInformationReqiest(size_t xCoord, size_t yCoord, eRequest infRequest);

    void gameWindowCloseEvent();
signals:
    void reportStatusToGui(eREPORT_LEVEL level,
                       const QString& tag,
                       const QString& report);
};

#endif // UIFACADE_H
