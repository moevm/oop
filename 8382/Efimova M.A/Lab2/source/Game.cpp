#include "Game.h"
#include "Infantry.h"
#include <QDebug>
#include "UItoBackendConnector.h"
#include "PongoBaseBoardUnit.h"

Game* Game::mInstance = nullptr;

Game* Game::getInstance() {
	if (mInstance == nullptr) {
		mInstance = new Game();
	}
	return mInstance;
}

void Game::initGUI(int argc, char* argv[]) {
	qInfo() << "--------------------Game Start----------------------";
	qInfo() << " ";
	//Initialize GUI
	qmlRegisterSingletonType<UItoBackendConnector>("game", 1, 0, "UIConnector", UItoBackendConnector::UItoBackendConnector_singletonTypeProvider);
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	_qApp = new QGuiApplication(argc, argv);
	_qEngine = new QQmlApplicationEngine();
	const QUrl url(QStringLiteral("qrc:/main.qml"));	//Path to main GUI file
	QObject::connect(_qEngine, &QQmlApplicationEngine::objectCreated,
		_qApp, [url](QObject* obj, const QUrl& objUrl) {
			if (!obj && url == objUrl)
				QCoreApplication::exit(-1);				//If there is no such file
		}, Qt::QueuedConnection);
	QObject::connect(_qEngine, &QQmlApplicationEngine::quit, _qApp, &QGuiApplication::quit);
	_qEngine->load(url);
}

int Game::Start() {
	return _qApp->exec();
}

void Game::_debug_demo() {
	
}

void Game::initBoard(int sizeX, int sizeY, int maxAllowedUnits) {
	//_connector = UItoBackendConnector::getInstance();
	//Initializze game board and rules
	qInfo() << "initializing board";
	auto boardProp = new Board::BoardProperties;
	boardProp->sizeX = sizeX;
	boardProp->sizeY = sizeY;
	boardProp->maxAllowedUnits = maxAllowedUnits;
	mGameBoard = new Board(boardProp);
	auto base = new PongoBaseBoardUnit();
	if (!mGameBoard->getCellAt(4, 9).isEmpty)
		mGameBoard->removeUnit(4, 9);
	mGameBoard->addUnit(base, 4, 9);
	//mGameBoard->_debug_print();
}

Board* Game::getBoard() {
	return mGameBoard;
}

void Game::playerAction(Board::BoardCell fromCell, Board::BoardCell toCell, int actionID) {
	auto unit = dynamic_cast<PlayableBoardUnit*>(fromCell.unit);
	if (unit != nullptr) {
		auto metaVec = unit->userAction(toCell, actionID);
		auto meta = metaVec[0];
		if (meta.isCreate) {
			mGameBoard->addUnit(meta.createdUnit, meta.unitX, meta.unitY);
		}
		if (meta.isMove) {
			mGameBoard->moveUnit(unit, meta.moveX, meta.moveY);
		}
	}
	cellsToUpdate.push_back(std::pair<int, int>(fromCell.x, fromCell.y));
	cellsToUpdate.push_back(std::pair<int, int>(toCell.x, toCell.y));
}

std::vector<std::pair<int, int>> Game::getCellsToUpdate() {
	return cellsToUpdate;
}


