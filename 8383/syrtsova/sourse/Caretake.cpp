#include "pch.h"
#include "Caretaker.h"



Caretaker::Caretaker(Originator *originator) : _originator(originator) {
	this->_originator = originator;
}

void Caretaker::backup(Game<Rules>* game, bool& isUnitSelected, bool& logToFile, bool& logToTerminal, bool& withoutLog, Units* selectedUnit, int& currNumBase) {
	memento = this->_originator->save(game, isUnitSelected, logToFile, logToTerminal, withoutLog, selectedUnit, currNumBase);
}

void Caretaker::undo(Game<Rules>* game, bool& isUnitSelected, bool& logToFile, bool& logToTerminal, bool& withoutLog, int& currNumBase) {
	this->_originator->restore(game, isUnitSelected, logToFile, logToTerminal, withoutLog, currNumBase);
}

