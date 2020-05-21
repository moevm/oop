#ifndef UIFACADE_H
#define UIFACADE_H

#include <QApplication>
#include <QScreen>
#include <QDebug>

#include "GUI/mainwindow.h"
#include "InformationHeaders/commandPar.h"
#include "Game/GameProcess/gameprocess.h"
#include "GameField/Coords.h"

#include "FacadeMediator.h"
#include "Game/Logging/Loggers/ILogAdapter.h"
#include "Game/Logging/Loggers/loggers.h"
#include "Game/Logging/Loggers/logadapter.h"

#include "Game/Saving/gamemementocaretacker.h"
#include "GUI/IVisualizer.h"

class UIFacade : public QObject, public std::enable_shared_from_this<UIFacade>
{
    Q_OBJECT

public:
    UIFacade(int argc, char *argv[]);
    ~UIFacade() = default;

    friend class Visualizer;

    void start();
    void receiveStrAnswer(std::string answer);

private:
    QApplication *application;
    // GUI
    std::shared_ptr<MainWindow> window;
    // Game
    std::weak_ptr<IGameProcess> game;
    // Logger
    std::shared_ptr<ILogAdapter> logger;
    eLOGGER_OUTPUT_FORMAT loggerFormat;

    // Window show preparation
    void guiSetup();
    [[nodiscard]] QByteArray readStyleSheetFile(const QString &filePath);

    // Memento work
    std::shared_ptr<GameMementoCaretacker> mementoCaretacker;

    // Visualization
    std::shared_ptr<IVisualizer> visualizer;

public slots:
    void createFieldRequest(size_t fieldSize, size_t playersCount, GAME_RULES_TYPE type);
    void createLoggerRequest(eLOGGER_TYPE type, eLOGGER_OUTPUT_FORMAT format);
    void addBaseRequest(eBaseType baseType, size_t xCoord, size_t yCoord, QString name);
    void addUnitRequest(eUnitsType unitType, QString sourceBaseName);
    void moveUnitReguest(size_t xSource, size_t ySource, size_t xDest, size_t yDist);
    void attackUnitRequest(size_t xSource, size_t ySource, size_t xDest, size_t yDist);
    void cellInformationReqiest(size_t xCoord, size_t yCoord, eRequest infRequest);

    void gameWindowCloseEvent();
    void saveGameRequest(std::string fileName);
    void loadGameRequest(std::string fileName);
signals:
    void reportStatusToGui(eREPORT_LEVEL level,
                       const QString& tag,
                       const QString& report);
    void restoreBaseNameGui(QString name);
};

#endif // UIFACADE_H
