#include"cell_ancestors.h"
cell init();
class playing_field {

	int max_obj;
	int height;
	int width;
	cell** p_f;

public:

	
	playing_field(int height, int width);
	playing_field(const playing_field& ob2);//Конструктор копии


	void remove_obj(int i, int j);
	playing_field() {

		max_obj = 0;
		height = width = 0;
		p_f = nullptr;

		std::cout << "Объект создан с помощью конструктора без параметров\n\n";

	}

	void inic_cell(int i, int j);//клетка
	//Для след функций можно сделать проверку указателя p_f
	char* type_cell(int i, int j) {

		
			return p_f[i][j].get_type();

	}


	int health_cell(int i, int j) {

		return p_f[i][j].get_health();
	}

	int attack_cell(int i, int j) {

		return p_f[i][j].get_attack_force();

	}

	int drug_cell(int i, int j) {

		return p_f[i][j].get_paracetomol();
	}

	void output_field();
	int get_height() {
		return height;

	}

	int get_width() {
		
		return width;
	}

	//cell get_cell(int i,int j){
		
	//	cell ob;
	//	ob = p_f[i][j];
		
	//	return ob;//конструктор копии?
	//}
	
	char* get_type(int i, int j){
		return p_f[i][j].get_type();
	}

	char* get_kind(int i, int j){
		return p_f[i][j].get_kind();
	}
	void move(int i1, int j, int i2, int j2);

	playing_field operator=(playing_field& ob);
	
	~playing_field();


};


