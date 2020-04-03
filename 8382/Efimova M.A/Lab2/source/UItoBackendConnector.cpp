#include "UItoBackendConnector.h"
#include "PlayableBoardUnit.h"
#include <QDebug>

UItoBackendConnector* UItoBackendConnector::mInstance = nullptr;

UItoBackendConnector::UItoBackendConnector(QObject* parent) {
	mGame = Game::getInstance();
}

QObject* UItoBackendConnector::UItoBackendConnector_singletonTypeProvider(QQmlEngine* engine, QJSEngine* scriptEngine) {
	Q_UNUSED(engine)
	Q_UNUSED(scriptEngine)

	auto connector = new UItoBackendConnector();
	mInstance = connector;
	return connector;
}

UItoBackendConnector* UItoBackendConnector::getInstance() {
	return mInstance;
}

QJsonArray UItoBackendConnector::initBoard(int sizeX, int sizeY, int maxAllowedUnits) {
	mGame->initBoard(sizeX, sizeY, maxAllowedUnits);
	QJsonArray arr;
	for (int i = 0; i < sizeY; i++) {
		QJsonArray tarr;
		for (int j = 0; j < sizeX; j++) {
			QJsonObject cell;
			Board::BoardCell tcell = mGame->getBoard()->getCellAt(j, i);
			cell.insert("terrain_unit", tcell.terrainUnit->getName().c_str());
			if (!tcell.isEmpty) {
				cell.insert("board_unit", tcell.unit->getName().c_str());
			}
			else
				cell.insert("board_unit", "empty");
			tarr.append(cell);
		}
		arr.append(tarr);
	}
	return arr;
}

QJsonObject UItoBackendConnector::getBoardUnitAtCell(int x, int y) {
	auto cell = mGame->getBoard()->getCellAt(x, y);
	QJsonObject cellObject{ {"x", x}, {"y", y} };
	QJsonObject terrainUnit;
	terrainUnit.insert("name", cell.terrainUnit->getName().c_str());
	cellObject.insert("terrain_unit", terrainUnit);
	if (!cell.isEmpty) {
		QJsonObject boardUnit;
		boardUnit.insert("name", QString(cell.unit->getName().c_str()));
		auto playable_unit = dynamic_cast<PlayableBoardUnit*>(cell.unit);
		if (playable_unit != nullptr) {
			QJsonObject stats{
				{"health", playable_unit->getStats().health},
				{"armor", playable_unit->getStats().armor},
				{"attack", playable_unit->getStats().attack}
			};
			boardUnit.insert("hasStats", 1);
			boardUnit.insert("stats", stats);
		}
		else
			boardUnit.insert("hasStats", 0);
		cellObject.insert("board_unit", boardUnit);
	}
	else {
		QJsonObject boardUnit;
		boardUnit.insert("name", "empty");
		cellObject.insert("board_unit", boardUnit);
	}
	return cellObject;
}

QJsonArray UItoBackendConnector::getUpdatedCells() {
	auto arr = mGame->getCellsToUpdate();
	QJsonArray cells;
	for (int i = 0; i < arr.size(); i++) {
		auto cellObject = getBoardUnitAtCell(arr[i].first, arr[i].second);
		cells.append(cellObject);
	}
	return cells;
}

void UItoBackendConnector::action(QJsonObject action) {
	QJsonObject invokingCellObj = action.value("invoking_cell").toObject();
	auto targetCellObj = action.value("target_cell").toObject();
	auto invokingCell = mGame->
		getBoard()->
		getCellAt(invokingCellObj.value("x").toInt(), invokingCellObj.value("y").toInt());
	auto targetCell = mGame->
		getBoard()->
		getCellAt(targetCellObj.value("x").toInt(), targetCellObj.value("y").toInt());
	int actionID = action.value("action_id").toInt();
	mGame->playerAction(invokingCell, targetCell, actionID);
	emit boardChanged();

}
