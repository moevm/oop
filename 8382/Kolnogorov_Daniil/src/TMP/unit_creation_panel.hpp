#pragma once

#include "floating_panel.hpp"

class Renderer;

class UnitCreationPanel : FloatingPanel {
public:
    Renderer* renderer;

    // all units available for creation
    vector<UnitInterface*> available_units;
    unsigned selected_unit;

    UnitCreationPanel(Renderer* renderer);

    void render(Rectangle rect);
    void handle_click() override;
};
