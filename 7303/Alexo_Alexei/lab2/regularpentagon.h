#ifndef REGULARPENTAGON_H
#define REGULARPENTAGON_H

#include <vector>
#include "shape.h"

class RegularPentagon: public Shape{
public:
    RegularPentagon(Color color, Point center, int lenght);
    void Scale(double coefficient) override;
    friend ostream &operator << (ostream &out, const RegularPentagon& regularPentagon);

private:
    int lenght;
};

#endif // REGULARPENTAGON_H
