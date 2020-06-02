#pragma once
#include <exception>

using namespace std;
/// Класс обработчика ошибок типа "Некорректный символ"
class error1 : public exception {//некорректный символ
public:     explicit error1(char a) { this->a = a; }
			virtual const char* what() const throw()
			{
				return "Некорректный ввод.\n";
			}
			void printErr()
			{
				cout << "Символ \"" << a << "\" не цифра.\n";
			}
private:     char a;
};

/// Класс обработчика ошибок типа "Некорректная цифра"
class error2 : public exception {//некорректный символ
public:     explicit error2(char a) { this->a = a; }
			virtual const char* what() const throw()
			{
				return "Некорректный ввод.\n";
			}
			void printErr()
			{
				cout << "Цифры \"" << a << "\" нет в меню выбора.\n";
			}
private:     char a;
};