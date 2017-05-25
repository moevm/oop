#pragma once
#ifndef GRAPH_H
#define GRAPH_H
#include <algorithm>
#include <vector>
#include <iostream>
#include <queue>
#include <random>
#include <fstream>
#include <functional>
#include<climits>
#include <string>
#include "BinTree.h"
//template<class T>

//void GraphGenerator(size_t Vnumber,std::vector<std::vector<T>> &matrix)
//{

//}
////Вершина графа///

///Очередь с приоритетом///
/*
template <class T>
struct Priority_Q
{
std::vector<SV<T>> SV_;
Priority_Q() :SV_(nullptr)
{}
Priority_Q(const std::vector<SV<T>> val)
{
SV_ = val;
}
int FindMin() //поиск вершины с минимальным приоритетом
{
int rmin = SV_[0].top_;
int buffer = 0;
for (size_t count = 1; count<SV_.size(); count++) {

if ((SV_[buffer].priority_>SV_[count].priority_))
buffer = count;

}
rmin = SV_[buffer].top_;
return rmin;

}
bool isEmpty()
{

return (SV_.empty());
}
void deleteTop(size_t top) //удалить вершину
{
for (size_t count = 0; count<SV_.size(); count++) {
if (SV_[count].top_ == top) {

SV_.erase(SV_.begin() + count);

return;
}
}
return;
}
void reduceKey(size_t top, size_t parent, size_t priority) //измение параметров вершины
{
for (size_t count = 0; count<SV_.size(); count++) {
if (SV_[count].top_ == top) {
SV_[count].priority_ = priority;
SV_[count].parent_ = parent;
return;
}
}

}

bool real(size_t top) //проверка на существование вершины
{
for (size_t count = 0; count<SV_.size(); ++count) {
if (top == SV_[count].top_)
return true;
}
return false;

}

};
*/
///Реализация графа///
template <class T>
class graph {
public:
	void YPD(); //алгоритм Прима (Я-Прима-Дейкстры)
	graph() :graph_(nullptr), V(0)
	{}

	graph(std::vector<std::vector<T>> buffer) :graph_(buffer), V(buffer.size())
	{}
private:
	std::vector<std::vector<T>> graph_; // статья про векторы http://www.prog.org.ru/topic_27860_0.html
	size_t V;

};

template <class T>
void graph<T>::YPD()
{
	std::vector<SV<T>> var(V);
	for (size_t i = 0; i<V; i++) {
		if (i == 0)
			var.at(i).add(i, 0, 0);
		else
			var.at(i).add(i, 1000000, 0);//INFINITY не работает

	}
	//Priority_Q<T> Q(var);
	BinTree <T> Q(var);
	Q.show();
	while (!Q.isEmpty()) {
		//  for (size_t count=0;count<Q.SV_.size();count++) {
		//      std::cout<<"TOP"<<Q.SV_[count].top_<<" pr"<<Q.SV_[count].priority_<<std::endl;
		//  }

		//size_t tempV = Q.FindMin();
		size_t tempV = Q.extractMin();
		for (size_t count = 0; count<V; count++) {

			if ((graph_[tempV][count] != 0) && (var[count].priority_>graph_[tempV][count]) && (Q.real(count)))  //&&(Q.real(Q.SV_[count].top_))
			{
				var.at(count).priority_ = graph_[tempV][count];
				var.at(count).parent_ = tempV;
				Q.reduceKey(var.at(count).top_, var.at(count).parent_, var.at(count).priority_);

			}


		}
		//Q.deleteTop(tempV);
	}
	std::cout << "TOP" << std::endl;
	for (size_t count = 0; count<V; count++)
		std::cout << var[count].top_ << " ";
	std::cout << std::endl << "Prior" << std::endl;
	for (size_t count = 0; count<V; count++)
		std::cout << var[count].priority_ << " ";
	std::cout << std::endl << "Parent" << std::endl;
	for (size_t count = 0; count<V; count++)
		std::cout << var[count].parent_ << " ";

}



void GraphGenerator(size_t Vnumber, std::vector<std::vector<double>> &matrix);  //принимает размер графа и матрицу

void TestGenerator(int t, int Vnumber); //принимает количество тестовых файлов и размер графа


void GraphGenerator(size_t Vnumber, std::vector<std::vector<double>> &matrix) {
	std::random_device generator; // генератор настоящих случайных чисел
	std::uniform_real_distribution<double> distr(0, 10); // равномерное распределение в диапазоне от 1 до 10
	auto real_random = std::bind(distr, std::ref(generator)); // обертка для удобного вызова функции

	for (int j = 0; j < Vnumber; ++j) {
		matrix[j].resize(Vnumber);
	}

	for (int i = 0; i<Vnumber; i++) {
		for (int j = 0; j<Vnumber; j++) {
			matrix[i][j] = matrix[j][i] = real_random();
		}
	}
}

void TestGenerator(int t, int Vnumber) {
	for (int i = 0; i<t; i++) {
		std::ofstream fout;
		std::string name = "";
		name += "test";
		name.append(std::to_string(i));
		name += ".txt";
		fout.open(name);

		std::vector<std::vector<double>> v(Vnumber);

		GraphGenerator(10, v);

		for (int i = 0; i<Vnumber; i++) {
			for (int j = 0; j<Vnumber; j++) {
				fout << v[i][j] << " ";
			}
			fout << '\n';
		}
	}
}



#endif // GRAPH_H
