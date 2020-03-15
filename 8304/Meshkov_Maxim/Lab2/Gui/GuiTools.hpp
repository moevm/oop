#pragma once

#include <string>
#include <raylib.h>

#include "../Units/Unit.hpp"
#include "../Terrains/Terrain.hpp"

class GuiTools {
public:
    static std::string getUnitMark(const Unit &unit);
    static std::string getUnitDescription(const Unit &unit, bool withIsIced = false);
    static Color getTerrainColor(const std::shared_ptr<const Terrain> &terrain);

    static void drawTextInHorizontalCenter(const std::string &text, int fontSize, Color color, int &y);
    static void drawCurtain();

    struct Offset {
        int x = 0, y = 0;
    };
    struct AreaSize {
        int width = 0, height = 0;
    };

    static void drawUnitInSquare(Rectangle square, const Unit &unit, int fontSize, Color fontColor);
};
