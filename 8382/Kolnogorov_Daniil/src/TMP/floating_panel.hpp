#pragma once

#include "click_handler.hpp"
#include "units.hpp"
#include <raylib.h>

class Renderer;

class FloatingPanel : ClickHandler {
protected:
    Renderer* renderer;
    // TODO
    // HoverHandler* next = nullptr;
public:
    FloatingPanel(Renderer* renderer);
    virtual void render(Rectangle rect) = 0;
    void handle_click() {
        if (next)
            next->handle_click();
    };
};
