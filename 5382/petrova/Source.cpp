
#include "string"
#include <locale>
#include "Shape.h"
#include "iostream"

using namespace std;
double x, y;


void coor()
{
	cout << "Ââåäèòå êîîðäèíàòû x è y :\n";
	cout << "x = ";
	cin >> x;
	cout << "y = ";
	cin >> y;
}
int main()
{
	setlocale(LC_ALL, "Russian");
	int choice = 0;
	while (true)
	{
		cout << "Âûáåðèòå äåéñòâèå: " << endl;
		cout << "1.Âûâåñòè èíôîðìàöèþ îá ýëëèïñå" << endl;
		cout << "2.Âûâåñòè èíôîðìàöèþ î ñåãìåíòå ýëëèïñà" << endl;
		cout << "3.Âûâåñòè èíôîðìàöèþ î ïàðàëëåëîãðàììå" << endl;
		cout << "4.Âûõîä" << endl;

		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			int R, r;
			coor();
			Point center = { x,y };
			cout << "Ââåäèòå áîëüøèé ðàäèóñ ýëëèïñà: ";
			cin >> R;
			cout << "Ââåäèòå ìåíüøèé ðàäèóñ ýëëèïñà: ";
			cin >> r;
			Ellips E(center, R, r);
			cout << "Ââåäèòå êîîðäèíàòû öåíòðà ýëëèïñà: ";
			Point new_center = { 2,3 };
			E.move(new_center);
			cout << "Ââåäèòå öâåò: ";
			my_color color = { 0.2, 0.7, 0.4 };
			cout << "Èçìåíèòå ðàçìåð ýëëèïñà: ";
			E.changesize(3);
			system("cls");
		}
		case 2:
		{
			int  x1, x2, y1, y2;
			coor();
			Point center = { x,y };
			cout << "Ââåäèòå êîîðäèíàòû ëåâîãî êîíöà: ";
			cin >> x1;
			cin >> y1;
			Point left = { x1,y1 };
			cout << "Ââåäèòå êîîðäèíàòû ïðàâîãî êîíöà: ";
			cin >> x2;
			cin >> y2;
			Point right = { x2,y2 };
			SegEl S(center, left, right);
			system("cls");

		}
		case 3:
		{
			int l, L;
			coor();
			Point center = { x,y };
			cout << "Ââåäèòå ðàññòîÿíèå îò öåíòðà äî âåðøèí : ";
			cin >> l;
			cin >> L;
			Parallelogramm P(center, l, L);
			system("cls");

		}
		case 4: exit(0);
		default:break;
		}
	}

	system("pause");
	return 0;
}
