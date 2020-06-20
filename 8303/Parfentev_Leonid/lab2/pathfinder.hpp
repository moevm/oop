#ifndef _H_PATHFINDER_HPP
#define _H_PATHFINDER_HPP

#include <map>
#include <queue>

#include "point.hpp"
#include "map.hpp"


class PathFinder {
    MapIter _start;
    Vec2 _end;
    int _max;

    struct Vec2WithCmp {
        Vec2 v;

        bool operator<(Vec2WithCmp o) const
        {
            if (v.y() == o.v.y())
                return v.x() < o.v.x();
            return v.y() < o.v.y();
        }
    };

    struct Pt2 {
        Vec2 pt;
        int depth;

        static Pt2 zero() { return {Vec2{0, 0}, 0}; }

        Pt2(Vec2 pt, int depth=0)
            :pt{pt}, depth{depth} {}

        Pt2 toDirection(int dir) const;

        bool pt_equal(Vec2 pt2)
        {
            return pt == pt2;
        }
    };

    std::map<Vec2WithCmp, int> _dirs {};
    std::queue<Pt2> _frontier {{Pt2::zero()}};

public:
    PathFinder(MapIter from, MapIter to, int max_steps)
        :_start{from},
         _end{to.point()},
         _max{max_steps} {}

    bool run();
};

#endif
