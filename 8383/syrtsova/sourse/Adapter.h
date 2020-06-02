#pragma once
#include "Target.h"
#include "Proxy.h"

/// Адаптер

/**
* Делает адаптируемый класс совместимым с целивым интерфейсом
*/

class Adapter : public Target
{
public:
	/// Обращение к функциям из "Recorder" через "Proxy"
	Proxy* _write;
	/// Конструткор Адаптера
	Adapter(Proxy* write);
	/// Переопределяемая функция для записи события
	bool request(std::string str) override;
};