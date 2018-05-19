#ifndef LAB2_SQUARE_H
#define LAB2_SQUARE_H

#include <vector>
#include "Parallelogram.h"

class Square : public Parallelogram {
public:
	// по двум диагоналям
	Square(std::string color, double side);
	std::string toString() const override;
};
#endif //LAB2_SQUARE_H