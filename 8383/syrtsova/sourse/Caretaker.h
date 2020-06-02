#pragma once
#include "Originator.h"
/// Класс Опекун

/**
* Опекун не зависит от класса Конкретного Снимка. Таким обзраом, он не имеет доступа к состоянию создателя, хранящемуся внутри снимка. 
* Он работает со всеми снимками через базовый интерфейс Снимка
*/

class Caretaker {
private:
	///Интерфейс снимка
	Memento* memento = nullptr;
	///Организатор записи и чтения данных
	Originator *_originator;

public:
	///Конструктор опекуна
	Caretaker(Originator *originator);
	///Функция записи текущего состояния 
	void backup(Game<Rules>* game, bool& isUnitSelected, bool& logToFile, bool& logToTerminal, bool& withoutLog, Units* selectedUnit, int& currNumBase);
	///Функция восстановления прошлой записи
	void undo(Game<Rules>* game, bool& isUnitSelected, bool& logToFile, bool& logToTerminal, bool& withoutLog, int& currNumBase);
};
