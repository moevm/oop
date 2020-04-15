#pragma once

#include <cstdint>
#include "Trivia/Point.h"

class Landscape;


class LandscapeFactory {
public:
    Landscape* produce(uint8_t landscapeType, Point point);
};
