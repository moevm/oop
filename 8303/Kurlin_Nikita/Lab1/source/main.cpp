#include <iostream>

using namespace std;

class Health {
public:
	int health;
};

class Armor {
public:
	int armor;
};

class Attack {
public:
	int attack;
};

class Unit : public Health, public Armor, public Attack {

public:
	int x;
	int y;

	//Функция перемещения
	void move(int x, int y) {
		this->x = x;
		this->y = y;

	}
};

class GameField {

	int x;
	int y;
	int unitCount;
	int maxCount;
	Unit*** unitsMap;	//Двумерный массив указателей на юнитов на поле

public:
	GameField(int x, int y, int maxCount) : x(x), y(y), unitCount(0), maxCount(maxCount) {
		
		unitsMap = new Unit** [y];
		
		for (int i = 0; i < y; i++) {
			unitsMap[i] = new Unit*[x];
			for (int j = 0; j < x; j++)
				unitsMap[i][j] = 0;
		}
	}

	//Конструктор копирования
	GameField(const GameField &field) : x(field.x), y(field.y), unitCount(field.unitCount), maxCount(field.maxCount), unitsMap(new Unit** [field.y]){
		for (int i = 0; i < y; i++) {
			unitsMap[i] = new Unit*[x];
			for (int j = 0; j < x; j++)
				unitsMap[i][j] = field.unitsMap[i][j];
		}
	}

	//Конструктор перемещения
	GameField(GameField &&field) : x(field.x), y(field.y), unitCount(field.unitCount), maxCount(field.maxCount), unitsMap(new Unit**[field.y]) {
		for (int i = 0; i < y; i++) {
			unitsMap[i] = new Unit*[x];
			for (int j = 0; j < x; j++)
				unitsMap[i][j] = field.unitsMap[i][j];
		}
	}
	void addUnit(Unit& unit) {
		if ((unit.x <= x - 1) && (unit.y <= y - 1)) {
			if (unitCount < maxCount) {
				unitsMap[unit.y][unit.x] = &unit;
				unitCount++;
			}
		}
	}

	void deleteUnit(Unit& unit) {
		for (int i = 0; i < y; i++) {
			for (int j = 0; j < x; j++) {
				if (&unit == unitsMap[i][j]) {
					unitsMap[i][j] = 0;
					unitCount--;
					return;
				}
			}
		}	
	}

	void moveUnit(Unit &unit, int x, int y) {
		deleteUnit(unit);
		unit.move(x, y);
		addUnit(unit);
	}

	void printAll() {
		for (int i = 0; i < y; i++) {
			for (int j = 0; j < x; j++) {
				if (unitsMap[i][j] != 0) {
					cout << 1;					
				}
				else
					cout << 0;
			}
			cout << endl;
		}
	}
};

class Infantry : public Unit {

};

class Archers : public Unit {

};

class Cavalry : public Unit {

};

class Swordsman : public Infantry{

public:
	Swordsman(int x, int y) {
		this->x = x;
		this->y = y;
		armor = 50;
		health = 70;
		attack = 20;
	}
};

class Spearman : public Infantry {

public:
	Spearman(int x, int y) {
		this->x = x;
		this->y = y;
		armor = 60;
		health = 70;
		attack = 15;
	}
};

class Longbow : public Archers {

public:
	 Longbow(int x, int y) {
		this->x = x;
		this->y = y;
		armor = 20;
		health = 100;
		attack = 10;
	}
};

class Flatbow : public Archers {

public:
	Flatbow(int x, int y) {
		this->x = x;
		this->y = y;
		armor = 20;
		health = 100;
		attack = 15;
	}
};

class Hussar : public Cavalry{

public:
	Hussar(int x, int y) {
		this->x = x;
		this->y = y;
		armor = 25;
		health = 70;
		attack = 15;
	}
};

class Dragoon : public Cavalry {

public:
	Dragoon(int x, int y) {
		this->x = x;
		this->y = y;
		armor = 30;
		health = 70;
		attack = 25;
	}
};
int main() {
	
	GameField Field(7, 7, 10);
	Spearman spear(3, 5);
	Spearman spear2(3, 3);
	Swordsman sword(4, 6);
	Swordsman sword2(0, 0);
	Field.addUnit(spear);
	Field.addUnit(spear2);
	Field.addUnit(sword);
	Field.addUnit(sword2);
	Field.printAll();
	cout << "*********************" << endl;

	Field.deleteUnit(sword);
	Field.deleteUnit(spear);
	Field.printAll();
	cout << "*********************" << endl;

	Field.moveUnit(spear2, 1, 1);
	GameField Field2(Field);
	Field2.printAll();

	return 0;
}