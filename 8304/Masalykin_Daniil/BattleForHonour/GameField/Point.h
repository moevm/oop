#ifndef BATTLEFORHONOUR_POINT_H
#define BATTLEFORHONOUR_POINT_H


class Point {

public:
    int x, y;

    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }

    Point() :
            x(0),
            y(0){}

    bool operator!=(Point &other) const {
        return !(x == other.x && y == other.y);
    }

    bool operator!=(Point other) const {
        return !(x == other.x && y == other.y);
    }

    bool operator==(Point &other) const {
        return x == other.x && y == other.y;
    }

    bool operator==(Point other) const {
        return x == other.x && y == other.y;
    }

};

#endif //BATTLEFORHONOUR_POINT_H
