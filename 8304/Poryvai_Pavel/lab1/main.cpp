#include"playing_field.h"
#include"cell_ancestors.h"

int main()
{
	
	int x,y,a,b;
	std::cout<<"\n Введите размер поля(формат:x,y)\n";
	cin>>x>>y;


	playing_field ob1(x, y);
	ob1.output_field();
	
	std::cout<<"\n Какую клетку инициализировать?(формат:строка,столбец)\n";
	cin>>x>>y;


	ob1.inic_cell(x, y);
	ob1.output_field();
	
	std::cout<<"\nПередвинуть объект по полю(Куда строка\столбец откуда строка\столбец)\n";
	std::cin>>x>>y>>a>>b;
	ob1.move(x, y, a, b);
	ob1.output_field();
	
	std::cout<<"\nУдалить юнит(строка\столбец)\n";
	cin>>x>>y;
	ob1.remove_obj(x, y);
	ob1.output_field();
	
	
	std::cout<<"\nДалее создается единичный объект типа клетка, его необходимо инициализировать\n";

	cell ob;
        ob = init();
        std::cout << ob.get_type();



	

	return 0;
}

