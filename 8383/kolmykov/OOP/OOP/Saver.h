#pragma once
#include "Field.h"
#include <fstream>
#include "TowerSnapshot.h"
#include "UnitSnapshot.h"
#include "ObjectSnapshot.h"


class Saver
{
private:
	std::shared_ptr<Field> field;
	std::ofstream file;
	void writeLastCell(int x, int y);
	void writeCell(int x, int y);
	void saveLand(std::shared_ptr<Land> land);
	void saveTower(std::shared_ptr<Tower> tower);
	void saveUnit(std::shared_ptr<Unit> unit);
	void saveObject(std::shared_ptr<NeutralObject> object);
public:
	Saver(std::shared_ptr<Field> field);
	~Saver();
	void save();
};

