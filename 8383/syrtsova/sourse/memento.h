#pragma once
#include "iostream"

/// Класс Снимок

/**
* Интерфейс Снимка представляет способ извлечения метаданных сникм. Однако он не расскрывает состояние Создателя
*/
class Memento {
public:
	virtual std::string& state() const = 0;
};