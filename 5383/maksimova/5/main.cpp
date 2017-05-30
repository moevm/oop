#include "Lab5.h"
int main() {
	//Алгоритмы из моего задания имеются в <algorithm>

//******* Проверка что все элементы диапазона удовлетворяют определенному критерию. ********

	//Генерируем случайные фигуры в количестве 1000 шт.
	stepik::vector< stepik::shared_ptr<Shape> > shapes = generate_conteiner(1000);

	//Проверяем, выполним ли предикат для всех элементов контейнера. 
	if (std::all_of(shapes.begin(), shapes.end(), Shape::common_side)) {
		std::cout << "Все элементы данного контейнера имеют общую сторону" <<std::endl;
	}
	else {
		std::cout << "Не все элементы данного контейнера имеют общую сторону" << std::endl;
	}

//******* Заменить элементы, соответствующие критерию, копируя весь диапазон. *******

	//Заменим все элементы, поподающие под предикат, на квадрат. 
	std::vector<Dot> my_square = { Dot(1, 1), Dot(1, 3), Dot(3, 3), Dot(3, 1) }; // Тот самый квадрат
	stepik::vector< stepik::shared_ptr<Shape> > new_shapes(1000);// новый контейнер куда скопируется

	std::replace_copy_if(shapes.begin(), shapes.end(), new_shapes.begin(),
		Shape::common_side, my_square);

	return 0;
}