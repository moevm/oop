#include "stdafx.h"
#include "AlgorithmsForShapes.h"


stepik::vector<shared_ptr<Shape>> generateFigures(int size)
{
	stepik::vector<shared_ptr<Shape>> vect_a(size);

	for (int i = 0; i < size; i++)
	{
		int figureType = rand() % 3;
		switch (figureType)
		{
			case 0:
			{
				vect_a[i] = shared_ptr<Shape>(new Rectangle({ 0,0 }, 20, 10));
				break;
			}
			case 1:
			{
				vect_a[i] = shared_ptr<Shape>(new Circle({ 0,0 }, 4));
				break;
			}
			case 2:
			{
				vect_a[i] = shared_ptr<Shape>(new Trapeze({ 2, 6 }, { 7, 6 }, { 8, 0 }, { 0,0 }));
				break;
			}
		}

	}
	return vect_a;
}

int compareFigures(const void * x1, const void * x2)
{
	return (*(*(shared_ptr<Shape>*)x1)).getSquare() - (*(*(shared_ptr<Shape>*)x2)).getSquare();
}

// Проверка двух упорядоченных диапазонов на равенство по определенному критерию
// Критерий - одинаковая площадь
bool isSimiliarRegion(Region r1, Region r2, const stepik::vector<shared_ptr<Shape>>& vect_a)
{
	stepik::vector<shared_ptr<Shape>> a(vect_a.begin() + r1.start, vect_a.begin() + r1.finish);
	stepik::vector<shared_ptr<Shape>> b(vect_a.begin() + r2.start, vect_a.begin() + r2.finish);

	qsort(&a[0], a.size(), sizeof(shared_ptr<Shape>), compareFigures);
	qsort(&b[0], b.size(), sizeof(shared_ptr<Shape>), compareFigures);

	for (int i = 0; i < a.size(); i++)
	{
		double square1 = (*a[i]).getSquare();
		double square2 = (*b[i]).getSquare();
		if (square1 != square2)
			return false;
	}

	return true;
}

// Упорядочить элементы, пока первые n элементов не будут следовать в требуемом порядке.
// Критерий - площадь
void sortFirstNElements(stepik::vector<shared_ptr<Shape>>& vect_a, int n)
{
	qsort(&vect_a[0], n, sizeof(shared_ptr<Shape>), compareFigures);
}

void printVector(const stepik::vector<shared_ptr<Shape>>& vect_a)
{
	for (int i = 0; i < vect_a.size(); i++)
		cout << i << " Figure Square: " << (*vect_a[i]).getSquare() << "\n";
}

void print2Vectors(const stepik::vector<shared_ptr<Shape>>& a, const stepik::vector<shared_ptr<Shape>>& b)
{
	for (int i = 0; i < a.size(); i++)
	{
		double square1 = (*a[i]).getSquare();
		double square2 = (*b[i]).getSquare();
		cout << i << ":\n 1 Figure Square: " << square1 << "\n" << " 2 Figure Square: " << square2 << "\n\n";
	}
}