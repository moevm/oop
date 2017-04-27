//Необходимо спроектировать систему классов для моделирования геометрических фигур: эллипс, сектор эллипса, параллелограм
//Задание предполагает использование виртуальных функций в иерархии наследования, проектирование и использование абстрактного базового класса. 
//Разработанные классы должны быть наследниками абстрактного класса Shape, содержащего методы для перемещения в указанные координаты, 
//поворота на заданный угол, масштабирования на заданный коэффициент, установки и получения цвета, а также оператор вывода в поток.
//Необходимо также обеспечить однозначную идентификацию каждого объекта.
//Решение должно содержать:условие задания;UML диаграмму разработанных классов;текстовое обоснование проектных решений;реализацию классов
#include "2.h"
size_t Shape::counter = 0;
std::ostream& operator<< (std::ostream& os, Shape& p) 
{
	p.print(os); 
	return os; 
} 
void Shape::setColor(Color newcolor)
{
	color = newcolor;
}
Color Shape :: getColor() const //получение цвета
{
	return color;
}

void Ellipse::print(std::ostream& os) 
{ 
	os<< "Id: " << id << std::endl; 
}
void Ellipse ::  move(int dx, int dy) {//перемещение
	center.x+=dx;
 	center.y+=dy;
}
void Ellipse :: rotate(int angle) { //поворот на угол
	fi+=angle;
}
void Ellipse :: scale(int k)//масшабирование на коэффициент
{
	a=a*k;
	b=b*k;
}

void SectorOfEllipse::print(std::ostream& os) 
{ 
	os<< "Id: " << id << std::endl; 
}

Point Ellipse::getCenter() const
{
	return center;
}
unsigned int Ellipse::getAAxis()
{
    return a;
}
unsigned int Ellipse::getBAxis()
{
    return b;
}
unsigned int Ellipse::getAngle()
{
	return fi;
}

void SectorOfEllipse::split (Ellipse* ellipse, SectorOfEllipse* s1, SectorOfEllipse* s2, SectorOfEllipse* s3) {
	//у эллипса и его секторов координаты центра, полуоси и угол наклона будут одинаковыми
	if(ellipse)
	{
		Color ellipseColor = ellipse->getColor();
		Color colorS1(ellipseColor.red,0,0);
		Color colorS2(0,ellipseColor.green,0);
		Color colorS3(0,0,ellipseColor.blue);
	
		Point ellipseCenter = ellipse->getCenter();
		unsigned int a = ellipse->getAAxis();
		unsigned int b = ellipse->getBAxis();
		unsigned int angle = ellipse->getAngle();
		
		*s1 = SectorOfEllipse(colorS1, ellipseCenter, a, b, angle, 0, 120);
		*s2 = SectorOfEllipse(colorS2, ellipseCenter, a, b, angle, 120, 240);
		*s3 = SectorOfEllipse(colorS3, ellipseCenter, a, b, angle, 240, 360);
		delete ellipse;	
    }
}

bool SectorOfEllipse::operator ==(const SectorOfEllipse &other) const
{
    return(a == other.a &&
           b == other.b &&
           getColor() == other.getColor() &&
           getCenter() == other.getCenter() &&
           fi == other.fi &&
           f1 == other.f1 &&
           f2 == other.f2);
}
//Реализовать метод static void SectorOfEllipse::split(Ellipse* ellipse, SectorOfEllipse* s1, SectorOfEllipse* s2, SectorOfEllipse* s3), 
//который принимает эллипс и разрезает его на 3 непересекающихся сектора. Эллипс при этом должен удаляться. Цвет каждого сектора задаётся 
//одной из составляющих цвета исходного эллипса.
//Пример: был эллипс лимонного цвета(#F8F344). Получили s1 - красный(#F80000), s2 - зелёный(#00F300), s3 - синий(#000044).



bool checkParallelogram(Point a, Point b, Point c, Point d){//проверка на параллелограмм
	//разницами между x-вой координатой (а и в) должна быть такой же, как и у (c и d)
	//а разница между у-ковыми координатами (а и d)==(b и c)
	if( ((b.x-a.x)==(c.x-d.x)) & ((c.y-b.y)==(d.y-a.y)) ) return true;
	else return false;
}
void Parallelogram::print(std::ostream& os) 
{ 
	os<< "Id: " << id << std::endl; 
}
void Parallelogram ::  move(int dx, int dy) {//перемещение
	a.x+=dx;
 	a.y+=dy;
 	b.x+=dx;
 	b.y+=dy;
 	c.x+=dx;
 	c.y+=dy;
 	d.x+=dx;
 	d.y+=dy;
}
void Parallelogram :: rotate(int angle) { //поворот на угол
	angle=angle;
}
void Parallelogram :: scale(int k)//масшабирование на коэффициент
{
	a.x*=k;
 	a.y*=k;
 	b.x*=k;
 	b.y*=k;
 	c.x*=k;
 	c.y*=k;
 	d.x*=k;
 	d.y*=k;
}
