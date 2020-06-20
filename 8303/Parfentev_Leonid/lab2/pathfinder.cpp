#include <map>
#include <queue>

#include "map.hpp"
#include "point.hpp"
#include "pathfinder.hpp"


PathFinder::Pt2
PathFinder::Pt2::toDirection(int dir) const
{
    // assert(dir >= 0 && dir < 8);

    int d1 = (dir + 1) % 8;
    int dx = (d1 % 4 == 3) ? 0 : (d1 < 4) ? 1 : -1,
        dy = (dir % 4 == 0) ? 0 : (dir < 4) ? 1 : -1;

    return Pt2{pt.shifted({dx, dy}), depth + 1};
}

bool
PathFinder::run()
{
    Vec2 start_pt = _start.point();

    while (!_frontier.empty()) {
        Pt2 current = _frontier.front();
        _frontier.pop();

        if (start_pt.shifted(current.pt) == _end)
            return true;

        if (_max >= 0
            && current.depth >= _max)
            continue;

        Vec2WithCmp cur_v2wc {current.pt};
        auto iter = _dirs.find(cur_v2wc);
        if (iter == _dirs.end())
            _dirs[cur_v2wc] = -1;

        for (int i = 0; i < 8; ++i) {
            Pt2 shifted_delta = current.toDirection(i);

            Vec2WithCmp sh_v2wc {shifted_delta.pt};
            auto iter = _dirs.find(sh_v2wc);
            if (iter != _dirs.end())
                continue;

            MapIter shifted = _start.shifted(shifted_delta.pt);
            if (!shifted.valid()
                || shifted.unit())
                continue;

            _frontier.push(shifted_delta);
        }
    }

    return false;
}
