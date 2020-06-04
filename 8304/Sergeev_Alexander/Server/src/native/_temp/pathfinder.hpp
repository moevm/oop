#ifndef LOGIC_PATHFINDER_HPP
#define LOGIC_PATHFINDER_HPP

#include "../base/includes.hpp"
#include "../tiles/base_tile.hpp"
#include "../tilemap/square.hpp"

#define m_max(a, b)            (((a) > (b)) ? (a) : (b))
#define m_min(a, b)            (((a) < (b)) ? (a) : (b))



class pathfinder {
public:
    explicit pathfinder(tilemap::square &map);
    ~pathfinder() = default;

    std::list<stts::vector2<int>> find_path(const stts::vector2<int>& from, const stts::vector2<int>& to);

private:
    static tilemap::abstract_tilemap* map;
    std::list<stts::vector2<int>> open_list;
    stts::vector2<int> begin_node;
    stts::vector2<int> end_node;
    std::list<stts::vector2<int>> free_list;
    std::list<stts::vector2<int>> path;

    bool can_walk(const stts::vector2<int>& from, const stts::vector2<int>& to);

    void identify_successors(stts::vector2<int>& node);
    stts::vector2<int> jump(int x, int y, int px, int py);
    std::vector<stts::vector2<int>> find_neighbors(stts::vector2<int>& cellNode);
    void backtrace(const stts::vector2<int>& node);
    std::list<stts::vector2<int>> expand_path();
    std::vector<stts::vector2<int>> interpolate(int x0, int y0, int x1, int y1);


    int manhattan(int x, int y) { // TODO: (probably) move this to a_tilemap when WE will be done.
        return x + y;
    }

    int octile(int dx, int dy) { // TODO: (probably) move this to a_tilemap when WE will be done.
        double F = sqrt(2) - 1;
        return (int)(dx < dy ? F * dx + dy : F * dy + dx);
    }
};


#endif //LOGIC_PATHFINDER_HPP
