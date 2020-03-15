#include "GuiTools.hpp"

#include "GuiConstants.hpp"
#include "../Terrains/GroundTerrain.hpp"
#include "../Terrains/StoneTerrain.hpp"
#include "../Terrains/WaterTerrain.hpp"

std::string GuiTools::getUnitMark(const Unit &unit) {
    return unit.getName().substr(0, 1);
}

std::string GuiTools::getUnitDescription(const Unit &unit, bool withIsIced) {
    std::string description =
            "Health: " + std::to_string(unit.getHealth()) + "\n" +
            "Hit: " + std::to_string(unit.getHit()) + "\n" +
            "Ices when attacks: " + (unit.icesWhenAttacks() ? "yes" : "no") + "\n" +
            "Armor: " + std::to_string(unit.getArmor()) + "\n" +
            "Move range: " + std::to_string(unit.getMoveRange()) + "\n" +
            "Attack range: " + std::to_string(unit.getAttackRange());
    if (withIsIced) {
        description += std::string("\n") + "Is iced: " + (unit.isIced() ? "yes" : "no");
    }
    return description;
}

Color GuiTools::getTerrainColor(const std::shared_ptr<const Terrain> &terrain) {
    if (dynamic_cast<const GroundTerrain *>(terrain.get())) {
        return groundColor;
    }
    if (dynamic_cast<const StoneTerrain *>(terrain.get())) {
        return stoneColor;
    }
    if (dynamic_cast<const WaterTerrain *>(terrain.get())) {
        return waterColor;
    }
    return BLANK;
}

void GuiTools::drawTextInHorizontalCenter(const std::string &text, int fontSize, Color color, int &y) {
    float spacing = (float)fontSize / 5.0f;//10.0f;
    Vector2 textSize = MeasureTextEx(GetFontDefault(), text.c_str(), (float)fontSize, spacing);
    DrawTextEx(GetFontDefault(), text.c_str(),
               {(float)GetScreenWidth() / 2 - textSize.x / 2, (float)y}, (float)fontSize, spacing, color);
    y += (int)textSize.y;
}

void GuiTools::drawCurtain() {
    DrawRectangleRec({0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, curtainColor);
}

void GuiTools::drawUnitInSquare(Rectangle square, const Unit &unit, int fontSize, Color fontColor) {
    auto mark = GuiTools::getUnitMark(unit);
    int textWidth = MeasureText(mark.c_str(), fontSize);
    int textOffsetX = (square.width - textWidth) / 2;
    int textOffsetY = (square.height - fontSize) / 2;
    DrawText(mark.c_str(), square.x + textOffsetX,
             square.y + textOffsetY, fontSize, fontColor);
}
