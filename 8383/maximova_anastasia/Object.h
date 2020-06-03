#pragma once

 class Object { //абстрактный класс
protected:
	int x;
	int y;
	int view;
	char name[2];

public:
	virtual void setName(char symbol) = 0;
	virtual void setView(int type) = 0;
	virtual void setXY(int x, int y) = 0;
	virtual char* getName() = 0;
	virtual int getView() = 0;
	virtual int getX() = 0;
	virtual int getY() = 0;
};
