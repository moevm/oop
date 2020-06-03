#include "Game.h"
#include "Infantry.h"
#include <QDebug>

Game* Game::mInstance = nullptr; //обнуляем экземпляр класса

Game* Game::getInstance() { // если пустой, то выделяем память
	if (mInstance == nullptr) { 
		mInstance = new Game();
	}
	return mInstance; //возвращаем экземпляр нашего класса
}

void Game::Init(int argc, char* argv[]) {
	qInfo() << "--------------------Game Start----------------------";
	qInfo() << " ";
	//Initialize GUI
	/*QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	_qApp = new QGuiApplication(argc, argv);
	_qEngine = new QQmlApplicationEngine();
	const QUrl url(QStringLiteral("qrc:/main.qml"));	//Path to main GUI file
	QObject::connect(_qEngine, &QQmlApplicationEngine::objectCreated,
		_qApp, [url](QObject* obj, const QUrl& objUrl) {
			if (!obj && url == objUrl)
				QCoreApplication::exit(-1);				//If there is no such file
		}, Qt::QueuedConnection);
	_qEngine->load(url);*/

	
	//инициализация доски с параметрами 
	auto boardProp = new Board::BoardProperties;
	boardProp->sizeX = 7; //по иксу
	boardProp->sizeY = 6; //по игрику
	boardProp->maxAllowedUnits = 10; //кол-во наших юнитов
	mGameBoard = new Board(boardProp); // выделяем память под доску
	mGameBoard->_debug_print(); //печатаем
}

int Game::Start() {
	return _qApp->exec(); //приост. выполнение текущ. процесса. Те стираем текущий процесс для запуска нового
}

void Game::_debug_demo() { //примеры, добавляем два юнита на доску, один удаляем по указателю, а второй перемещ. и удаляется по координатам
	auto factory = new InfantryFactory(); // выделяем память

	
		mGameBoard->addUnit(factory->getType(0), 0, 0); //добавляется два юнита на доску
		mGameBoard->addUnit(factory->getType(1), 1, 0);
		mGameBoard->_debug_print();
		mGameBoard->removeUnit(mGameBoard->operator()(0, 0)); //один удаляем по указателю
		mGameBoard->_debug_print();
		mGameBoard->moveUnit(mGameBoard->operator()(1, 0), 4, 5); //второй перемещается и удаляем по координатам
		mGameBoard->_debug_print();
		mGameBoard->removeUnit(4, 5);
		mGameBoard->_debug_print();
	}

