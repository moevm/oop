//
// Created by kholk on 28.05.2020.
//

#include "../Headers/NtrlObj.h"

std::vector<char> Oasis::who() {
    return {'K', 'S', 'A', 'R', 'C', 'H'};
}

ObjEffect Oasis::get() {
    return str.execute(100);
}


std::vector<char> Crocodile::who() {
    return {'K', 'S', 'A', 'R', 'C'};
}

ObjEffect Crocodile::get() {
    return str.execute(-20);
}

std::vector<char> PowerStatue::who() {
    return {'K', 'S', 'A', 'R', 'C', 'H'};
}

ObjEffect PowerStatue::get() {
    return str.execute(15);
}

std::vector<char> RangeStatue::who() {
    return {'K', 'S'};
}

ObjEffect RangeStatue::get() {
    return str.execute(1);
}
