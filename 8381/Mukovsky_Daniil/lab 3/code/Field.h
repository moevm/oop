#pragma once
#include <iostream>
#include "Unit.h"
#include "Landscape.h"
#include <list>
#include "observerField_andItems.h"
#include "Object.h"
#include "UnitInteractionMediator.h"
//#include <SFML/Graphics.hpp>

enum lands { ground, water, mountain };

class PlayingField : public IField
{
private:
	unsigned width;
	unsigned length;
	unsigned maxNumberOfElements;
	unsigned currentNumberOfElements;

	UnitInteractionMediator unitInteraction;

	class Cell
	{
	private:

		FieldObject* fieldObject_; //юнит или объекты
		Landscape* landscape; // ландшафт


	public:
		Cell();
		Cell(const Cell& copyCell);
		Cell& operator=(const Cell& copyCell);

		Cell(Cell&& copyCell)noexcept;
		Cell& operator=(Cell&& copyCell)noexcept;
		Landscape* getLandscapePtr() { return landscape; }
		FieldObject* getObjectPtr();
		bool isOccupied();
		void setObjectPtr(FieldObject* newObjectPtr);
		void setLandscapePtr(Landscape* newLandscape) {
			if (landscape)
				delete landscape;
			landscape = newLandscape;
		}
	};
	Cell** field;
	struct Coord
	{
		unsigned x;
		unsigned y;
	};

	void onObjectDestroyed(FieldObject* destroyedObject) {
		this->deleteObject(destroyedObject);
	}

public:
	PlayingField(unsigned width_ = 20, unsigned length_ = 20);

	PlayingField(const PlayingField& copyField);
	PlayingField(PlayingField&& copyField)noexcept;
	PlayingField& operator=(const PlayingField& playingField);
	PlayingField& operator=(PlayingField&& playingField)noexcept;

	~PlayingField();
	bool addObject(FieldObject* newObject, unsigned X, unsigned Y);
	bool checkCoordinate(unsigned x, unsigned y) const;
	void setCellLandscape(Landscape* landscape, unsigned X, unsigned Y) {
		field[Y][X].setLandscapePtr(landscape);
	}

	void setRandomLandscape();
	bool commitInteraction(unsigned X_old, unsigned Y_old, unsigned X_new, unsigned Y_new, bool curPlayer, bool interaction);//heal or attack

	bool moveUnit(unsigned X_old, unsigned Y_old, unsigned X_new, unsigned Y_new, bool curPlayer);

	void deleteObject(FieldObject* obj);
	void deleteObject(unsigned X, unsigned Y);
	void showConsoleField();
	void showConsoleLandscape();
	int getCurrentElements();
	void setMaxNumberOfElements(unsigned newValue);
	void setLandscape(std::vector<char> map);
	void setRandomObjects();
	void setObjects(std::vector<char> map);

	FieldObject* getUnitPtr(unsigned X, unsigned Y) {
		if (checkCoordinate(X, Y))
			if (field[Y][X].getObjectPtr()->getAbstractClass() == "Unit") {
				return field[Y][X].getObjectPtr();
			}
		return nullptr;
	}

	FieldObject* getObjectPtr(unsigned X, unsigned Y) {
		if (checkCoordinate(X, Y))
			if (field[Y][X].getObjectPtr()) {
				return field[Y][X].getObjectPtr();
			}
		return nullptr;
	}

	bool addUnit(FieldObject* newObject, unsigned X, unsigned Y);


	void checkUnitAndLandscape(FieldObject* unit) {
		Coord c = findObjectCoordinates(unit);
		int X = c.x;
		int Y = c.y;
		Landscape* proxyLand = field[Y][X].getLandscapePtr();
		proxyLand->canHoldFieldObject(unit);
	}
	std::string getInfoCell(int X, int Y);
	bool checkUnitAndLandscape(unsigned X, unsigned Y) {
		Landscape* proxyLand = field[Y][X].getLandscapePtr();
		proxyLand->checkUnitRange(field[Y][X].getObjectPtr());
		proxyLand->canHoldFieldObject(field[Y][X].getObjectPtr());
		if (!field[Y][X].getObjectPtr()) return false;
		return true;
	}

	Coord findObjectCoordinates(FieldObject* unit) {
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < length; j++) {
				if (field[i][j].getObjectPtr() == unit) {
					Coord c;
					c.x = j;
					c.y = i;
					return c;
				}
			}
		}
	}
};