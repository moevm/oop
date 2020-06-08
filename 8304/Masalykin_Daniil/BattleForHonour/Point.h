#ifndef BATTLEFORHONOUR_POINT_H
#define BATTLEFORHONOUR_POINT_H


class Point {

public:
    int x, y;

    Point();
    Point(int x, int y);

    bool operator!=(Point &other) const;
    bool operator!=(Point other) const;
    bool operator==(Point &other) const;
    bool operator==(Point other) const;


};

#endif //BATTLEFORHONOUR_POINT_H
