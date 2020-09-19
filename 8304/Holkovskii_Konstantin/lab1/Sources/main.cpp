#include "../Headers/Field.h"

int main() {
	Field a(20,20);
	a.addUnit({0,0},'K');

	a.move({0,0},{4,5});
	a.show();
	std::cout << std::endl;
    Field b(a);
    b.remUnit({4,5});
    b.show();
	return 0;
}
