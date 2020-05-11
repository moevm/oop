#include "unit_creation_panel.hpp"

UnitCreationPanel::UnitCreationPanel(Renderer* renderer) : renderer(renderer) {
    available_units = {
        new UnitWarrior, new UnitKnight,    new UnitArcher,
        new UnitArbalet, new UnitMageFrost, new UnitMageFire,
    };
    selected_unit = 0;
}

void UnitCreationPanel::render(Rectangle rect) {
    float scale = 1.5;

    int spacing = 10 * scale;
    int margins = 10 * scale;
    float tile_size_scaled = TILE_SIZE * scale;

    int total_units = available_units.size();

    // Rectangle rect = renderer->positioner->rect_with_size(
    //     total_units * (tile_size_scaled + spacing) + margins,
    //     (tile_size_scaled + 20 * scale), BOTTOM_LEFT);

    DrawRectangleRounded(rect, 0.2, 8, {255, 255, 255, 220});
    DrawRectangleRoundedLines(rect, 0.2, 8, 3, BLACK);

    Rectangle unit_border = {rect.x + margins, rect.y + margins,
                             tile_size_scaled, tile_size_scaled};

    for (unsigned i = 0; i < available_units.size(); i++) {
        if (i == selected_unit) {
            DrawRectangleRoundedLines(unit_border, 0.2, 8, 2, ORANGE);
        }
        Vector2 center = center_of_rect(unit_border);
        renderer->render_unit(center, available_units[i], GRAY, scale);
        unit_border.x += tile_size_scaled + spacing;
    }

    string unit_info = available_units[selected_unit]->get_info();
    Rectangle rect_info =
        renderer->positioner->rect_for_text(unit_info, BOTTOM_LEFT);
    draw_text_rect(unit_info, rect_info);
}

void UnitCreationPanel::handle_click() {
    Vector2 mouse_pos = GetMousePosition();
    if (CheckCollisionPointRec(mouse_pos, rect)) {
        selected_unit =
            (mouse_pos.x - rect.x - margins) / (TILE_SIZE * scale + spacing);
    } else {
    }
