#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <cmath>
#include "Rhomb.h"
#include "square.h"
#include "Trapeze.h"
#include <string>

//////////////////////////////////////////
#define Parallelogram_Edge_A 3          //
#define Parallelogram_Edge_B 2          //
#define Parallelogram_Ñorner M_PI / 2   //
#define Parallelogram_Color "blue"      //
#define Parallelogram_Scale 2           //
#define TParallelogram_Motion -1, 1     //
#define Parallelogram_Rotate M_PI / 6   //
//////////////////////////////////////////

//////////////////////////////////
#define Rhomb_Width 12          //
#define Rhomb_Height 5          //
#define Rhomb_Color "yellow"    //
#define Rhomb_Scale 10          //
#define Rhomb_Motion 5, -9      //
#define Rhomb_Rotate M_PI / 3   //
//////////////////////////////////


//////////////////////////////////
#define Square_Side 10          //
#define Square_Color "red"      //
#define Square_Scale 10         //
#define Square_Motion 10, -10   //
#define Square_Rotate M_PI / 3  //
//////////////////////////////////

////////////////////////////////////
#define Trapeze_Base_Side 15      //
#define Trapeze_Height 5          //
#define Trapeze_AngleA M_PI/2     //
#define Trapeze_AngleB M_PI/2     //
#define Trapeze_Color "pink"     //
#define Trapeze_Scale 10          //
#define Trapeze_Motion 5, -9      //
#define Trapeze_Rotate M_PI / 3   //
////////////////////////////////////


void outputting_of_edges( Parallelogram &p)
{
	std::cout << std::to_string(p.getA()) << " " << std::to_string(p.getB()) << "\n";
}

void outputting_of_edges( Rhomb &r)
{
	std::cout << std::to_string(r.getA()) << "\n";
}

void outputting_of_edges(Square &r)
{
	std::cout << std::to_string(r.getA()) << "\n";
}

void outputting_of_edges(Trapeze &p)
{
	std::cout << std::to_string(p.getA()) << " " << std::to_string(p.getB()) << "\n";
}

int main() {

	///////////////////////////////////////////////////////////

	Parallelogram parallelogram(Parallelogram_Color, Parallelogram_Ñorner, Parallelogram_Edge_A, Parallelogram_Edge_B);
	std::cout << "Parallelogram edges before transform: ";	outputting_of_edges(parallelogram);

	parallelogram.scale(Parallelogram_Scale);
	parallelogram.rotate(Parallelogram_Rotate);
	parallelogram.translate(TParallelogram_Motion);

	std::cout << "Parallelogram edges after transform: ";	outputting_of_edges(parallelogram);
	std::cout << parallelogram << "\n";

	///////////////////////////////////////////////////////////

	Rhomb rhomb(Rhomb_Color, Rhomb_Width, Rhomb_Height);
	std::cout << "Rhomb edges before transform: "; outputting_of_edges(rhomb);

	rhomb.translate(Rhomb_Motion);
	rhomb.rotate(Rhomb_Rotate);
	rhomb.scale(Rhomb_Scale);

	std::cout << "Rhomb edges after transform: "; outputting_of_edges(rhomb);
	std::cout << rhomb << "\n";

	///////////////////////////////////////////////////////////

	Square square(Square_Color, Square_Side);
	std::cout << "Square edges before transform: "; outputting_of_edges(square);

	square.translate(Square_Motion);
	square.rotate(Square_Rotate);
	square.scale(Square_Scale);

	std::cout << "Square edges after transform: "; outputting_of_edges(square);
	std::cout << square << "\n";

	/////////////////////////////////////////////////////////////

	Trapeze trapeze(Trapeze_Color, Trapeze_AngleA, Trapeze_AngleB, Trapeze_Base_Side, Trapeze_Height);
	std::cout << "Trapeze edges before transform: "; outputting_of_edges(trapeze);

	trapeze.translate(Square_Motion);
	trapeze.rotate(Square_Rotate);
	trapeze.scale(Square_Scale);

	std::cout << "Square edges after transform: "; outputting_of_edges(trapeze);
	std::cout << trapeze << "\n";
	system("pause");
	return 0;
}