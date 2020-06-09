#pragma once
#include "Field.h"

class Iwinrul {
public:
	virtual int who_lose(field* F) =0;//return num of winers-base if win or -1
	virtual int who_next(int i)=0; //return 1 if same and -1 if other one
	virtual int starts(field* F)=0;
};


class ruls1: public Iwinrul {
public:
	
	virtual int who_lose(field* F);
	virtual int who_next(int i);
	virtual int starts(field* F);

};

class ruls2 : public Iwinrul {
	//побеждает кто-то, если все мертвы
public:
	virtual int who_lose(field* F);
	virtual int who_next(int i);
	virtual int starts(field* F);
};

