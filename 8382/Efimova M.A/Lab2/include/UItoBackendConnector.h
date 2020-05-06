#pragma once
#include <QObject>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include "Game.h"

class UItoBackendConnector : public QObject
{
	Q_OBJECT

public:
	explicit UItoBackendConnector(QObject* parent = nullptr);
	static QObject* UItoBackendConnector_singletonTypeProvider(QQmlEngine* engine, QJSEngine* scriptEngine);
	static UItoBackendConnector* getInstance();

	Q_INVOKABLE QJsonObject getBoardUnitAtCell(int x, int y);
	Q_INVOKABLE QJsonArray getUpdatedCells();
	//Q_INVOKABLE void initBoard(int sizeX, int sizeY, int maxAllowedUnits, QString seed);
	Q_INVOKABLE QJsonArray initBoard(int sizeX, int sizeY, int maxAllowedUnits);
	Q_INVOKABLE void action(QJsonObject action);

signals:
	void boardChanged();

protected:
	static UItoBackendConnector* mInstance;
	Game* mGame;
};

