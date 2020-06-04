#ifndef LOGIC_CHOREOGRAPHER_HPP
#define LOGIC_CHOREOGRAPHER_HPP

#include <memory>

//
// class choreographer {
// private:
//     static std::shared_ptr<choreographer> instance;
//     std::shared_ptr<tilemap> map;
//
// public:
//     enum movement_state { still, waiting, moving };
//     enum movement_priority { sedative = 0, high, medium, low };
//
//     static void init (std::shared_ptr<tilemap>& tilemap);
//     static std::shared_ptr<choreographer> get ();
//
//     int can_move (std::shared_ptr<unit_moving> mover, std::shared_ptr<coords> destination);
//     void move (std::shared_ptr<unit_moving> unit, std::shared_ptr<coords> destination);
//     std::shared_ptr<std::vector<coords>> find_way (std::shared_ptr<unit_moving> unit, std::shared_ptr<coords> destination);
//
//     void kill (std::shared_ptr<unit> unit);
// };
//
//
// std::shared_ptr<choreographer> choreographer::instance = nullptr;
//
// void choreographer::init (std::shared_ptr<tilemap>& tilemap) {
//     instance = std::make_shared<choreographer>();
//     instance->map = tilemap;
// }
//
// std::shared_ptr<choreographer> choreographer::get () {
//     return instance;
// }
//
//
// int choreographer::can_move (std::shared_ptr<unit_moving> mover, std::shared_ptr<coords> destination) {
//     /*coords current;
//     std::vector<std::shared_ptr<unit>> blockers;
//
//     for (int i = 0; i < destination->get_x() + mover->get_size(); ++i) {
//         current.set_x(i);
//         current.set_y(mover->get_pivot_position()->get_y());
//
//         std::shared_ptr<unit> blocker = map->get_unit(current);
//         if (blocker != nullptr) blockers.push_back(blocker);
//     }
//     for (int i = 0; i < destination->get_y() + mover->get_size(); ++i) {
//         current.set_y(i);
//         current.set_x(mover->get_pivot_position()->get_x());
//
//         std::shared_ptr<unit> blocker = map->get_unit(current);
//         if (blocker != nullptr) blockers.push_back(blocker);
//     }*/
//
//     return true;
// }
//
// void choreographer::move (std::shared_ptr<unit_moving> unit, std::shared_ptr<coords> destination) {
// }
//
// std::shared_ptr<std::vector<coords>> choreographer::find_way (std::shared_ptr<unit_moving> unit, std::shared_ptr<coords> destination) {
//     return std::shared_ptr<std::vector<coords>>();
// }
//
//
// void choreographer::kill (std::shared_ptr<unit> unit) {
//
// }


#endif //LOGIC_CHOREOGRAPHER_HPP
