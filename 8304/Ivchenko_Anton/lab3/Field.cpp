#include <iostream>
#include "Field.h"

Field::Field(int max, int _h, int  _w)
{

	this->h = _h;
	this->w = _w;
	this->qmax = max;
	cur = 0;

	field = new Object * *[h];

	for (int i = 0; i < h; i++) {

		field[i] = new Object * [w];

		for (int j = 0; j < w; j++)

			field[i][j] = nullptr;

	}std::cout << "Field created\n";

};
void Field::formLandscape() {

	for (int i = 0; i < h; i++) {

		for (int j = 0; j < w; j++) {
			
			int a = rand() % 20;
			int b = rand() % 1000;
			if (a < 10)
				field[i][j] = new Plain;
			else if (a < 14)
				field[i][j] = new Forest;
			else if (a < 17)
				field[i][j] = new Lake;
			else if (a < 20)
				field[i][j] = new Mountain;
			
			if (b < 5) {
				Neutral* ntr = new LegendaryItem;
				field[i][j]->setNeutral(ntr);

			}
			else if (b < 30) {
				Neutral* ntr = new ArmorKit;
				field[i][j]->setNeutral(ntr);
			}
			else if (b < 40) {
				Neutral* ntr = new WeaponKit;
				field[i][j]->setNeutral(ntr);
			}
			else if (b < 50) {
				Neutral* ntr = new SpeedBoost;
				field[i][j]->setNeutral(ntr);
			}
		}

	}


};

Object* Field::getCoords(int x, int y) {

	return field[x][y];

}
Base* Field::SetBase( int x, int y) {

	Base* base = new Base(x,y);
	field[x][y]->~Object();
	field[x][y] = base;

	return base;

};
void Field::AddObj(Unit* a, int x, int y) {


	if ((cur < qmax) && (0 < x < h) && (0 < y < h) && field[x][y]->getUnit() == nullptr && field[x][y]->IsAvailable()) {

		field[x][y]->SetUnit(a);
		a->setCoordinats(x, y);
		cur++;
		std::cout << "\nUnit added\n";
	}
	else
		std::cout << "Incorrect arguments";
}

void Field::RemObj(Unit* a, int x, int y) {

	if ((0 < x < h) && (0 < y < h) && (field[x][y]->getUnit() == a)) {

		field[x][y]->RemoveUnit();
		cur--;
		std::cout << "\nUnit removed\n";
	}
	else
		std::cout << "Incorrect arguments";

};

void Field::Moving(Unit* a, int posx, int posy, int dx, int dy) {

	if ((posx + dx > h || posx + dx < 0) && (posy + dy > w || posy + dy < 0)) {


		std::cout << "Incorrect arguments"; return;

	}
	/*if ((abs(dx) > a->getCharactresistics()->getSpeed())) {

		field[posx][posy]->RemoveUnit();
		int newx = posx + (a->getCharactresistics()->getSpeed() * dx / abs(dx));
		int newy = posx + (a->getCharactresistics()->getSpeed() * dy / abs(dy));

		field[posx + newx][posy + newy]->SetUnit(a);

		a->setCoordinats(posx + newx, posy + newy);

		std::cout << "\nUnit moved\n";
	}
	*/
	else {

		RemObj(a, posx, posy);

		AddObj(a, posx + dx, posy + dy);

		std::cout << "\nUnit moved\n";

	}



};

Field* Field::CopyField(Field* a) {

	for (int i = 0; i < h; i++) {

		for (int k = 0; k < w; k++) {

			a->SetUnit(field[i][k], i, k);

		}
	}return a;

};


void Field::SetUnit(Object* a, int b, int c) {

	field[b][c] = a;

};


void Field::PrintField() {

	for (int i = 0; i < h; i++) {

		std::cout << '\n';

		for (int k = 0; k < w; k++) {

			if (field[i][k]->getUnit() != nullptr)

				std::cout << field[i][k]->getUnit()->getid() << ' ';

			else if (field[i][k]->getNeutral() != nullptr)
				std::cout << field[i][k]->getNeutral()->getType() << ' '; 

			else
				std::cout << field[i][k]->getObj() << ' ';
		}
	};

};

Field::~Field() {

	delete[] field;
	std::cout << "\nField deleted\n";

};
