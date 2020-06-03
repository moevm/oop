#include "Game.h"
#include "Infantry.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include "UItoBackendConnector.h"
#include "PongoBaseBoardUnit.h"
#include "ActionDispatcher.h"
#include "Logger.h"
#include <fstream>
#include <sstream>
#include <random>

Game* Game::mInstance = nullptr;

Game* Game::getInstance() {
	if (mInstance == nullptr) {
		mInstance = new Game();
	}
	return mInstance;
}

void Game::initGUI(int argc, char* argv[]) {
	Logger::setLoggingMode(2);
	Logger::setVerboseLevel(3);
	Logger::log("Game", "Init");
	Logger::log("Game", "Initializing GUI");
	//Initialize GUI
	qmlRegisterSingletonType<UItoBackendConnector>("game", 1, 0, "UIConnector", UItoBackendConnector::UItoBackendConnector_singletonTypeProvider);
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	_qApp = new QGuiApplication(argc, argv);
	_qApp->setOrganizationName("somename");
	_qApp->setOrganizationDomain("somename");
	_qEngine = new QQmlApplicationEngine();
	const QUrl url(QStringLiteral("qrc:/main.qml"));	//Path to main GUI file
	QObject::connect(_qEngine, &QQmlApplicationEngine::objectCreated,
		_qApp, [url](QObject* obj, const QUrl& objUrl) {
			if (!obj && url == objUrl)
				QCoreApplication::exit(-1);				//If there is no such file
		}, Qt::QueuedConnection);
	QObject::connect(_qEngine, &QQmlApplicationEngine::quit, _qApp, &QGuiApplication::quit);
	_qEngine->load(url);
	Logger::log("Game", "Finished initializing GUI");
}

int Game::Start() {
	Logger::log("Game", "Game started");
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
	BoardUnit::resetUnitCount();
	PongoBoardUnit::resetUnitCount();
	mGameBoard = new Board(boardProp);
	//mGameBoard->_debug_print();
}

Board* Game::getBoard() {
	return mGameBoard;
}

void Game::playerAction(Board::BoardCell fromCell, Board::BoardCell toCell, int actionID) {
	auto unit = dynamic_cast<PlayableBoardUnit*>(fromCell.unit);
	changedCells->clear();
	if (unit != nullptr) {
		auto metaVec = unit->userAction(toCell, actionID);
		for (int i = 0; i < metaVec.size(); i++)
			mActionDispatcher->push_back(metaVec[i]);
		changedCells = mActionDispatcher->flush();
	}
	auto res = _rules->checkForEnd();
	if (res != -1) {
		Logger::log("Game", "Player \"" + _users[res]->getName() + "\" lost", 0);
	}
	else
		currentTurn = _rules->changeTurn();
}

std::vector<ActionDispatcher::Action>* Game::getCellsToUpdate() {
	return changedCells;
}

bool Game::save(std::string fileName) {
	auto fileStream = new std::fstream(fileName, std::ios::out | std::ios::trunc);

	if (!fileStream->good()) {
		fileStream->close();
		return 0;
	}

	auto boardSnapshot = mGameBoard->getSnapshot();

	QJsonDocument gameSnapshot(boardSnapshot);
	QString stringJson(gameSnapshot.toJson(QJsonDocument::Compact));

	qInfo() << stringJson;

	std::string stringJsonStd = stringJson.toStdString();

	(*fileStream) << stringJsonStd.c_str();

	fileStream->close();
	return 1;
}

bool Game::load(std::string fileName) {
	auto fileStream = new std::fstream(fileName, std::ios::in);

	if (!fileStream->good()) {
		fileStream->close();
		return 0;
	}

	std::string JsonStrStd;
	(*fileStream) >> JsonStrStd;

	BoardUnit::resetUnitCount();
	PongoBoardUnit::resetUnitCount();

	QString stringJson = QString::fromStdString(JsonStrStd);

	QJsonDocument gameSnapshot = QJsonDocument::fromJson(stringJson.toUtf8());

	QJsonObject boardSnapshot = gameSnapshot.object();

	//delete mGameBoard;

	mGameBoard = new Board(boardSnapshot);
	mActionDispatcher = new ActionDispatcher(mGameBoard);
	changedCells = new std::vector<ActionDispatcher::Action>;

	return 1;
}

void Game::initGame(int rulesetType, std::vector<std::string> users, int sizeX, int sizeY, int maxAllowedUnits) {
	for (int i = 0; i < users.size(); i++) {
		auto user = new User(users[i]);
		_users.push_back(user);
	}
	initBoard(sizeX, sizeY, maxAllowedUnits);
	_rules = new GameRulesClassic(_users, mGameBoard);
	_rules->initBoard();
	mActionDispatcher = new ActionDispatcher(mGameBoard);
	changedCells = new std::vector<ActionDispatcher::Action>;
}

Game::~Game() {
	Logger::log("Game", "Shutdown", 0);
}

BoardUnit::ActionMeta Game::checkPlayerAction(Board::BoardCell fromCell, Board::BoardCell toCell, int actionID) {
	auto unit = dynamic_cast<PlayableBoardUnit*>(fromCell.unit);
	if (unit != nullptr) {
		auto metaVec = unit->userAction(toCell, actionID);
		return metaVec[0];
	}
	else {
		BoardUnit::ActionMeta meta;
		return meta;
	}
}

User* Game::getCurrentUser() {
	return _users[currentTurn];
}


