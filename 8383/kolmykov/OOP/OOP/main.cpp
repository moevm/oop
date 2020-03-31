#include "Demo.h"
#include <Windows.h>


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	Demo demo = Demo();
	demo.start(true);
}