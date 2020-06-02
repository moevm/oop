#pragma once
#include "Memento.h"

/// Класс Конктретный снимок

/**
* Конкретный снимок содержит инфраструктуру для хранения состояния Создателя
*/
class ConcreteMemento : public Memento
{
private:
	std::string& fout;

public:
	ConcreteMemento(std::string& fout);
	std::string& state() const override {
		return fout;
	}
};