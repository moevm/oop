#pragma once
#include <iostream>
#include <cstring>
#define nullptr NULL
using namespace std;

class foot {
protected:
	char e_weapon_foot[50];
public:
	foot() {

		std::cout << "\n\n Создаем объект пехота\n";

	}
	~foot() {

		std::cout << "Удаление объекта пехота\n\n";
	}
	


};

class archers {//Поменять название
protected:
	char e_weapon_luchniki[50];
public:

	archers() {

		std::cout << "Создаем объект лучники\n";
	}
	~archers() {

		std::cout << "Удаление объекта лучники\n";
	}
	//
};

class cavalry {
protected:
	char e_weapon_konnica[50];
public://
	cavalry() {

		std::cout << "Создаем объект конница\n";

	}
	~cavalry() {

		std::cout << "Удаление объекта конница\n";
	}
};


class unit:public foot,public archers, public cavalry {
protected:

	char *type;
	char* kind;
	int health;
	int attack_force;
	int paracetomol;

public:

	char* get_type() {
		return type;
	};
	char* get_kind(){
		return kind;
	}

	int get_health() {
		return health;
	};

	int get_attack_force() {
		return attack_force;
	};

	int get_paracetomol() {
		return paracetomol;
	};

	unit() {

		std::cout << "Создается объект юнит\n";
		//strcpy_s(type, 50, "Пустая клетка");
		
	};

	~unit() {

		std::cout << " Удаляется объект юнит\n";
	}

	
};



class cell :public unit {

	int write_in;
public:

	cell() {

		std::cout << "Создается объект клетка \n\n";
		type = nullptr;
		kind = nullptr;
		write_in = 0;//Клетка пустая
		//strcpy_s(type, 50, "Пустая клетка");
	}

	cell(const cell& ob);//конструктор копии lvalue-reference
	//cell(cell && s);//rvalue-reference перемещающий конструктор
	//cell& operator=(cell && s);

	~cell() {//Для корректного удаления при выделении памяти под наследованый класс

		if (write_in == 1) {

			delete type;
			delete kind;
		}

		std::cout << "\n\nУдаление объекта клетки\n";
	}

	
	int is_writein() {
		return write_in;
	}

	bool operator==(cell& op2) {

		if (strcmp(this->type, op2.type) == 0 && strcmp(this->kind, op2.kind) == 0)
			return true;
		else
			return false;
	}

	void set(const char* type_s, const char *kind_s);

	cell operator=(const cell& ob);

	void remove() {

		if (write_in == 1) {
			delete kind;

			delete type;

			write_in = 0;
		}
		else if (write_in == 0) {

			std::cout << "\nКлетка уже пуста\n";

		}
			
	}
	
};

