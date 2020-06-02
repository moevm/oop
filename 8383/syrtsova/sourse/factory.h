#include "Warrior.h"
#include "Warlock.h"
#include "Archer.h"
#include "Map.h"
#include "Neutral.h"
#include "Adapter.h"

/// Абстрактная фабрика для производства 
/**
* Абстрактный класс содержит виртуальные функции создания юнитов.
*/
class Factory
{
public:
	/// Виртуальная функция создания мечника
	virtual Swordsman* createSwordsman(Map* field, Creating *neutral, Adapter *adapter, int x = 0, int = 0) = 0;
	/// Виртуальная функция создания мечника
	virtual Spear* createSpear(Map* field, Creating *neutral, Adapter *adapterб, int x = 0, int  = 0) = 0;
	/// Виртуальная функция создания мечника
	virtual Magician* createMagician(Map* field, Creating *neutral, Adapter *adapterб, int x, int y) = 0;
	/// Виртуальная функция создания мечника
	virtual Healer* createHealer(Map* field, Creating *neutral, Adapter *adapter, int x, int y) = 0;
	/// Виртуальная функция создания мечника
	virtual Archer* createArcher(Map* field, Creating *neutral, Adapter *adapter, int x, int y) = 0;
	/// Виртуальная функция создания мечника
	virtual Arbalester* createArbalester(Map* field, Creating *neutral, Adapter *adapter, int x, int y) = 0;
};
