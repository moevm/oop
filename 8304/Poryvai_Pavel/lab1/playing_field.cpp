#include"cell_ancestors.h"
#include"playing_field.h"

void playing_field::move(int i1, int j1, int i2, int j2) {

	std::cout << "\nВызвана функция move\n";
	p_f[i1][j1] = p_f[i2][j2];//вызывается конструктор копии;

	remove_obj(i2, j2);

}



void playing_field::remove_obj(int i, int j) {


	std::cout << "\nУдаляем юнит на клетке\n";
	p_f[i][j].remove();

}


 playing_field::~playing_field() {


	 if (p_f) {

		 for (int i = 0; i < height; i++) {

			 delete[] p_f[i];//таким образом удаляется массив объектов


		 }

		 delete p_f;
	 }

		 std::cout << "Объект поле удален\n";

	 

}
 





void playing_field::output_field() {





	for (int i = 0; i < height; i++) {


		std::cout << "\n";

		for (int j = 0; j < width; j++) {


			if (p_f[i][j].is_writein() == 1) {

				std::cout << p_f[i][j].get_type();
				std::cout << " ";
			}
			else if (p_f[i][j].is_writein() == 0) {

				std::cout << "Пустая клетка";
				std::cout << " ";


			}

		}

	}

		std::cout << "\n";

}

void playing_field::inic_cell(int i, int j) {

	std::cout << "\nВызвана инициализация клетки\n";


	p_f[i][j] = init();
	

}





playing_field::playing_field(int height, int width) {

	this->height = height;
	this->width = width;


	max_obj = height * width;

	p_f = new cell * [height];

	for (int i = 0; i < height; i++) {

		p_f[i] = new cell[width];
		
	}


	
	std::cout << "Поле создано c помощью конструктора с параметрами \n\n";
}


playing_field playing_field::operator=(playing_field &ob){

	
	std::cout<<"\nВызвана перегрузка оператора = для playing_field\n";

	height = ob.height;
	width = ob.width;
	max_obj = ob.max_obj;

	if(p_f != nullptr){

		for(int i = 0; i < height;i++)
			delete [] p_f[i];

		delete p_f;
	
	}

	p_f = new cell*[height];

	for(int i = 0; i < height; i++)
		p_f[i] = new cell[width];

	
	

	

	for(int i = 0; i < height; i++)
		
		for(int j = 0; j < width; j++){
			if(ob.p_f[i][j].is_writein() == 1)
				p_f[i][j].set(ob.get_type(i,j),ob.get_kind(i,j));
			
			
		}
			//p_f[i][j] = ob.get_cell(i,j);//здесь вызывается перегрузка и конструктор копии cell 

	return *this;
}


playing_field::playing_field(const playing_field &ob){// для =  он условный

	std::cout<<"\nВызван конструктор копии поля\n";
	
	p_f = new cell*[1];
	p_f[0] = new cell[1];
}


