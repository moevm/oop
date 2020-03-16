#include <iostream>
#include "Field.h"




Field::Field(int max, int _h, int  _w)
{
	this->h = _h;
	this->w = _w;
	this->qmax = max;
	cur = 0;
	field = new Unit * *[h];
	for (int i = 0; i < h; i++) {

		field[i] = new Unit * [w];
		for (int j = 0; j < w; j++) field[i][j] = nullptr;
	}
};



Field::Field(const Field& f) {

	this->qmax = f.qmax;
	this->h = f.h;
	this->w = f.w;
	this->cur = 0;
	this->field = new Unit * *[h];

	for (int i = 0; i < h; i++) {

		this->field[i] = new Unit * [w];
		for (int k = 0; k < w; k++) {

			this->field[i][k] = f.field[i][k];


		}
	}
};



Field& Field::operator =  (const Field& f) {

	this->qmax = f.qmax;
	this->h = f.h;
	this->w = f.w;
	this->cur = 0;

	if (this->field != nullptr)

		delete[] this->field;

	this->field = new Unit * *[h];

	for (int i = 0; i < h; i++) {

		this->field[i] = new Unit * [w];

		for (int k = 0; k < w; k++) {

			this->field[i][k] = f.field[i][k];
		}
	}
	return *this;

}



void Field::AddObj(Unit* a, int x, int y) {


	if ((cur < qmax) || (0 < x < h) || (0 < y < h)) {

		field[x][y] = a;
		cur++;

	}
	else
		std::cout << "Incorrect arguments";
};



void Field::RemObj(int x, int y) {

	if ((0 < x < h) || (0 < y < h)) {

		field[x][y] = nullptr;
		cur--;
	}
	else
		std::cout << "Incorrect arguments";

};


void Field:: Moving(Unit* a, int posx, int posy, int dx, int dy) {


	if ((dx > a->speed) && (posx + dx < h) && (posy + dy < w))
		std::cout << "Incorrect arguments";
	else {
		RemObj(posx, posy);
		AddObj(a, posx + dx, posy + dy);
	}

};


Field* Field::CopyField(Field* a) {

	for (int i = 0; i < h; i++) {
		for (int k = 0; k < w; k++) {
			a->SetUnit(field[i][k], i, k);

		}
	}return a;

};


void Field:: SetUnit(Unit* a, int b, int c) {

	field[b][c] = a;

};


void Field:: PrintField() {

	for (int i = 0; i < h; i++) {
		std::cout << '\n';
		for (int k = 0; k < w; k++) {
			if (field[i][k] == nullptr)
				std::cout << '0';
			else
				std::cout << field[i][k]->id;
		}
	};

};


Field::~Field()

{
	delete[] field;
}
