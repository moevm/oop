#ifndef OOP_OBJECT_H
#define OOP_OBJECT_H
#include <string>

typedef struct {
    int x;
    int y;
} Coordinates;

class Object{
public:
    virtual Coordinates* getCoordinates() = 0;
    virtual void setCoordinates(int, int) = 0;
    virtual char getName() = 0;
    virtual ~Object() = default;

};
#endif //OOP_OBJECT_H
