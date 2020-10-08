#include "../Headers/Game.h"

int main() {
    system("chcp 65001");
    Game a(5,5);
    a.select({0,0});
    a.addBase();
	a.addUnit({1,1},'K');
    a.addUnit({1,2}, 'H');
    a.show();
	std::cout << std::endl;
	a.select({1,1});
    a.Attack({1,2});
    a.Attack({1,2});
    a.Attack({1,2});
	a.show();
	std::cout << std::endl;
	return 0;
}