#include "pathfinder.hpp"

// TODO: (probably) clear this when WE will be done.

tilemap::abstract_tilemap* pathfinder::map;


pathfinder::pathfinder(tilemap::square &nmap) {
    map = &nmap;
}

std::list<stts::vector2<int>> pathfinder::find_path(const stts::vector2<int>& from, const stts::vector2<int>& to) {
     map->clear_tiles();
     path.clear();

     begin_node = from;
     end_node = to;

     // set the `g` and `f` value of the start node to be zero
     map->get_tile(begin_node).g = 0;
     map->get_tile(begin_node).f = 0;

     // push the begin node into the open list
     open_list.push_back(from);
     map->get_tile(begin_node).opened = true;

     stts::vector2<int> node;

     while (!open_list.empty()) {
         // pop the position of node which has the minimum `f` value.
         node = open_list.front();
         open_list.pop_front();
         map->get_tile(node).closed = true;
         if (node == to) {
             path.push_back(from);
             backtrace(to);
             return expand_path();
         }

         identify_successors(node);
     }

     return expand_path();
}



bool pathfinder::can_walk(const stts::vector2<int>& from, const stts::vector2<int>& to) {
     if (((to.x < 0) || (to.x >= map->get_scale().x)) || ((to.y < 0) || (to.y >= map->get_scale().y))) return false;
     tile::base_tile* node = &map->get_tile(to.x, to.y);
     return node && !node->is_occupied() && (abs(map->get_tile(to.x, to.y).get_height() - node->get_height()) < 20);
}

void pathfinder::identify_successors(stts::vector2<int>& node) {
     stts::vector2<int> jumpnode;
     int d = 0;
     int g = 0;

     std::vector<stts::vector2<int>> cells = find_neighbors(node);
     for (auto itr = cells.begin(); itr != cells.end(); ++itr) {
         auto result = jump((*itr).x, (*itr).y, node.x, node.y);

         int jx = result.x;
         int jy = result.y;
         if (jx < 0) // NEEDED????
             continue;

         jumpnode = result;
         if (map->get_tile(jumpnode).closed) continue;

         // include distance, as parent may not be immediately adjacent:
         d = octile(abs(jx - node.x), abs(jy - node.y));
         g = map->get_tile(node).g + d;

         if (!map->get_tile(jumpnode).opened || g < map->get_tile(jumpnode).g) {
             map->get_tile(jumpnode).g = g;
             if (map->get_tile(jumpnode).h == 0)
                 map->get_tile(jumpnode).h = manhattan(abs(jx - end_node.x), abs(jy - end_node.y));
             map->get_tile(jumpnode).f = map->get_tile(jumpnode).g + map->get_tile(jumpnode).h;
             map->get_tile(jumpnode).parent = node;

             if (!map->get_tile(jumpnode).opened) {
                 open_list.push_back(jumpnode);
                 open_list.sort([] (const stts::vector2<int> a, const stts::vector2<int> b)->bool // TODO: replace with in-place search.
                                 {
                                     return map->get_tile(a).f < map->get_tile(b).f;
                                 });

                 map->get_tile(jumpnode).opened = true;
             }
         }
     }
 }

stts::vector2<int> pathfinder::jump(int x, int y, int px, int py) {
     int dx = x - px;
     int dy = y - py;

     if (!can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x, y)))
         return stts::vector2<int>(-1, -1);

     if (stts::vector2<int>(x, y) == end_node)
         return stts::vector2<int>(x, y);

     // check for forced neighbors
     // along the diagonal
     if ( dx != 0 && dy != 0 ) {
         if ( (can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x - dx, y + dy)) && !can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x - dx, y)))
            || (can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x + dx, y - dy)) && !can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x, y - dy))) )
             return stts::vector2<int>(x, y);

         if ((jump(x + dx, y, x, y).x != -1) || (jump(x, y + dy, x, y).x != -1))
             return stts::vector2<int>(x, y);

     } else { // horizontally/vertically
         if (dx != 0) {
             if ((can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x + dx, y + 1)) && !can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x, y + 1)))
                || (can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x + dx, y - 1)) && !can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x, y - 1))) )
                 return stts::vector2<int>(x, y);

         } else {
             if ((can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x + 1, y + dy)) && !can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x + 1, y)))
                || (can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x - 1, y + dy)) && !can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x - 1, y))))
                 return stts::vector2<int>(x, y);
         }
     }

     return jump(x + dx, y + dy, x, y);
 }

 std::vector<stts::vector2<int>> pathfinder::find_neighbors(stts::vector2<int>& cellNode) {
     std::vector<stts::vector2<int>> neighbours;

     int x = cellNode.x;
     int y = cellNode.y;

     // directed pruning: can ignore most neighbors, unless forced.
     if (map->get_tile(cellNode).parent.is_set()) {
         // get the normalized direction of travel
         int dx = (x - map->get_tile(cellNode).parent.x) / m_max(abs(x - map->get_tile(cellNode).parent.x), 1);
         int dy = (y - map->get_tile(cellNode).parent.y) / m_max(abs(y - map->get_tile(cellNode).parent.y), 1);

         // search diagonally
         if ( dx != 0 && dy != 0 ) {
             if (can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x, y + dy))) // down
                 neighbours.push_back(stts::vector2<int>(x, y + dy));

             if (can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x + dx, y))) // right
                 neighbours.push_back(stts::vector2<int>(x + dx, y));

             if (can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x + dx, y + dy))) // right down
                 neighbours.push_back(stts::vector2<int>(x + dx, y + dy));

             if (!can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x - dx, y))) // 0 1
                 neighbours.push_back(stts::vector2<int>(x - dx, y + dy));

             if (!can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x, y - dy))) // 1 0
                 neighbours.push_back(stts::vector2<int>(x + dx, y - dy));
         } else { // search horizontally/vertically
             if ( dx == 0 ) {
                 if (can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x, y + dy)))
                     neighbours.push_back(stts::vector2<int>(x, y + dy));

                 if (!can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x + 1, y)))
                     neighbours.push_back(stts::vector2<int>(x + 1, y + dy));

                 if (!can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x - 1, y)))
                     neighbours.push_back(stts::vector2<int>(x - 1, y + dy));
             } else {
                 if (can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x + dx, y)))
                     neighbours.push_back(stts::vector2<int>(x + dx, y));

                 if (!can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x, y + 1)))
                     neighbours.push_back(stts::vector2<int>(x + dx, y + 1));

                 if (!can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x, y - 1)))
                     neighbours.push_back(stts::vector2<int>(x + dx, y - 1));
             }
         }
     } else {
         for (int i = -1; i <= 1; ++i) {
             for (int j = -1; j <= 1; ++j) {
                 if ((i == 0) && (j == 0)) continue;
                 if (can_walk(stts::vector2<int>(x, y), stts::vector2<int>(x + i, y + j))) neighbours.push_back(stts::vector2<int>(x + i, y + j));
             }
         }
     }

     return neighbours;
 }

 void pathfinder::backtrace(const stts::vector2<int>& node) {
     stts::vector2<int> node2(node);
     stts::vector2<int> point;

     do {
         point.x = node2.x;
         point.y = node2.y;
         path.push_back(point);

         node2 = map->get_tile(node2).parent;
     } while (map->get_tile(node2).parent.is_set());

     path.reverse();
 }

 std::list<stts::vector2<int>> pathfinder::expand_path() {
     std::list<stts::vector2<int>> lastpath;

     int len = (int) path.size();

     if (len < 2) return lastpath;

     auto itr = path.begin();
     auto itrnext = ++path.begin();
     int inc = 0;
     while (inc < len - 1) {
         std::vector<stts::vector2<int>> points = interpolate(itr->x, itr->y, itrnext->x, itrnext->y);
         int size = (int) points.size();
         for ( int i = 0; i < size - 1; ++i ) {
             lastpath.push_back(points[i]);
         }

         ++itr;
         ++itrnext;
         ++inc;
     }

     lastpath.push_back(*itr);

     return lastpath;
 }

 std::vector<stts::vector2<int>> pathfinder::interpolate(int x0, int y0, int x1, int y1) {
     std::vector<stts::vector2<int>> lines;

     int dx = abs(x1 - x0);
     int dy = abs(y1 - y0);

     int sx = (x0 < x1) ? 1 : -1;
     int sy = (y0 < y1) ? 1 : -1;

     int err = dx - dy;
     int e2 = 0;

     stts::vector2<int> point;

     while (true) {
         point.x = x0;
         point.y = y0;
         lines.push_back(point);

         if ((x0 == x1) && (y0 == y1)) break;

         e2 = 2 * err;

         if ( e2 > -dy ) {
             err -= dy;
             x0 += sx;
         }

         if ( e2 < dx ) {
             err += dx;
             y0 += sy;
         }
     }

     return lines;
 }
