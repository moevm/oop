#include "Shape.h"
#include <utility>


size_t Shape::counter = 0; // èíèöèàëèçàöèÿ ñòàòè÷åñêîãî ïîëÿ

//îïåðàòîð âûâîäà
std::ostream& operator <<(std::ostream& OS, const Shape& smth)//îïåðàòîð âûâîäà
{
	smth.print(OS);
	return OS;
}
//óñòàíîâèòü öâåò
void Shape::set_color(Color color) {//óñòàíîâèòü öâåò

	this->color = color;

}

//ïîëó÷èòü öâåò ôèãóðû
Color Shape::get_color() const { //ïîëó÷èòü öâåò

	return color;

}
//ïîëó÷èòü àéäè
size_t Shape::getId() const
{
	return id;
}

//ïåðåäâèíóòü
void Shape::move(Dot &new_v0) {
	double dx = corners[0].x - new_v0.x;
	double dy = corners[0].y - new_v0.y;
	for (int i = 0; i < corners.size(); i++) {
		corners[i].x -= dx;
		corners[i].y -= dy;
	}
}
//ðàññòÿíóòü
void  Shape::scale(double scale) {
	if (scale < 0) {
		throw std::invalid_argument("Ìàñøòàá íå ìîæåò áûòü îòðèöàòåëüíûì");
	}
	for (int i = 0; i < corners.size(); i++) {
		corners[i].x *= scale;
		corners[i].y *= scale;
	}
}
//ïîâåðíóòü ôèãóðó
void Shape::rotate(double new_angle) {
	Dot old_v0 = corners[0];
	move(Dot(0, 0));

	for (int i = 0; i < corners.size(); i++) {
		corners[i].rotate(new_angle);
	}
	move(old_v0);
}

//Èçóìèòåëüíîå çàäàíèå 
//Ðàáîòàåò íà ÷¸ðíîé ìàãèè
bool Shape::common_side(Shape* other) {

	//std::vector<Dot>common_dots; // îáùèå òî÷êè
	Dot cdot1;
	Dot cdot2;
	int dots = 0;
	//std::vector<Dot>old_this_corners = this->corners; // ñòàðûå âåðøèíû
	//std::vector<Dot>old_other_corners = other->corners;

	bool flag1 = false;
	bool flag2 = false;

	for (int i = 0; i < this->corners.size(); i++) {
		for (int j = 0; j < other->corners.size(); j++)
		{
			//íàõîäèì îáùèå òî÷êè
			if (this->corners[i] == other->corners[j]) {
				if (dots == 0) {
					cdot1 = corners[i];
					++dots;
				}
				else if (dots == 1) {
					cdot2 = corners[i];
					++dots;
				}
			}
		}
	}
	if (dots != 2) {
		return false; // åñëè íå íàøëè, òî ñòîðîíû íå ïåðåñåêàþòñÿ
	}

	for (int i = 0; i < other->corners.size(); i++) {
		if ((corners[i] == cdot1 && corners[(i + 1) % corners.size()] == cdot2) ||
			(corners[i] == cdot2 && corners[(i + 1) % corners.size()] == cdot1)) {
			flag1 = true;
		}
	}

	for (int i = 0; i < other->corners.size(); i++) {
		if ((other->corners[i] == cdot1 && other->corners[(i + 1) % corners.size()] == cdot2) ||
			(other->corners[i] == cdot2 && other->corners[(i + 1) % corners.size()] == cdot1)) {
			flag2 = true;
		}
	}

	return (flag1 && flag2);

	
}
Dot& Shape::min_y(Dot& a, Dot& b) const {
	if (a.y < b.y) {
		return a;
	}
	else {
		return b;
	}
}
Dot& Shape::max_y(Dot& a, Dot& b) const {
	if (a.y > b.y) {
		return a;
	}
	else {
		return b;
	}
}