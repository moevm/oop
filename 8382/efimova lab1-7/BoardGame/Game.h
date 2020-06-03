#pragma once
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Board.h"
class Game
{
public:
	static Game* getInstance(); //вызов экземпл€ра
	void Init(int argc, char* argv[]); //кьют
	int Start(); //вызываем
	void _debug_demo(); //собственно происход€т примеры
protected:
	static Game* mInstance; //указатель на экземпл€р 
	Board* mGameBoard = nullptr; //экземпл€р класса ƒоска
	
	QGuiApplication* _qApp;
	QQmlApplicationEngine* _qEngine;
};

