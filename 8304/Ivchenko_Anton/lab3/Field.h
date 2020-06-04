#pragma once
#include "Unit.h"
#include "Object.h"

class Field {

private:

	int h;
	int w;
	int cur;
	int qmax;
	Object*** field;

public:

	Field();
	Field(int max, int _h, int  _w);
	Base* SetBase(int x, int y);
	void AddObj(Unit* a, int x, int y);
	void RemObj(Unit* a, int x, int y);
	void Moving(Unit* a, int posx, int posy, int dx, int dy);
	Field* CopyField(Field* a);
	void SetUnit(Object* a, int b, int c);
	void PrintField();
	Object* getCoords(int, int);
	void formLandscape();
	void SetNeutralObjs();
	~Field();

};
