#pragma once
#include <iostream>
#include "Unit.h"
#include "Landscape.h"
#include <list>
#include "observerField_andItems.h"

//#include <SFML/Graphics.hpp>

enum lands { ground, water, mountain };

class PlayingField : public IField
{
private:
	int width;
	int length;
	int maxNumberOfElements;
	int currentNumberOfElements;

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
		int x;
		int y;
	};

	void onObjectDestroyed(FieldObject* destroyedObject) {
		this->deleteObject(destroyedObject);
	}

public:
	PlayingField(int width_ = 20, int length_ = 20);

	PlayingField(const PlayingField& copyField);
	PlayingField(PlayingField&& copyField)noexcept;
	PlayingField& operator=(const PlayingField& playingField);
	PlayingField& operator=(PlayingField&& playingField)noexcept;

	~PlayingField();
	bool addObject(FieldObject* newObject, int X = -1, int Y = -1);
	bool checkCoordinate(int x, int y) const;
	void setCellLandscape(Landscape* landscape, int X, int Y) {
		field[Y][X].setLandscapePtr(landscape);
	}

	void setRandomLandscape();
	void moveObject(int X_old, int Y_old, int X_new, int Y_new);
	void deleteObject(FieldObject* obj);
	void deleteObject(int X, int Y);
	void showConsoleField();
	void showConsoleLandscape();
	int getCurrentElements();
	void setMaxNumberOfElements(int newValue);
	void setLandscape(std::vector<char> map);


	void checkUnitAndLandscape(Unit* unit) {
		Coord c = findObjectCoordinates(unit);
		int X = c.x;
		int Y = c.y;
		std::cout << "Unit at X:" << X << " Y:" << Y << "\n";
		Landscape* proxyLand = field[Y][X].getLandscapePtr();
		proxyLand->canHoldUnit(unit);
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