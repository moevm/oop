#pragma once

class ClickHandler {
protected:
    ClickHandler* next = nullptr;

public:
    // ClickHandler();
    void set_next_handler(ClickHandler* handler) { next = handler; };
    virtual void handle_click() = 0;
};
