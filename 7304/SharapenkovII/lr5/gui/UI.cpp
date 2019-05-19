//
// Created by smokfyz on 12.04.19.
//

#include <iostream>
#include "../runtime/Game.h"
#include "UI.h"
#include "../impediment/StaticImpediment.h"

static UI *g_ui = nullptr;

UI::UI(Ref<Window> window) : window_(window) {
    int window_width = App::instance()->window()->width();
    int window_height = App::instance()->window()->height();
    overlay_ = Overlay::Create(window_, window_width, window_height, 0, 0);
    g_ui = this;

    view()->set_load_listener(this);
    view()->LoadURL("file:///field.html");
}

UI::~UI() {
    view()->set_load_listener(nullptr);
    g_ui = nullptr;
}

shared_ptr<char[]> UI::stringToChar(string s) {
    shared_ptr<char[]> imp_type = make_shared<char[]>(s.size() + 1);
    strcpy(imp_type.get(), s.c_str());

    return imp_type;
}

void UI::OnClose() {
}

void UI::OnResize(int width, int height) {
    RefPtr<Window> window = App::instance()->window();
    overlay_->Resize(window->width(), window->height());
}

void UI::OnDOMReady(ultralight::View* caller) {
    // Set the context for all subsequent JS* calls
    SetJSContext(view()->js_context());

    JSObject global = JSGlobalObject();

    createField = global["createField"];
    renderUnit = global["renderUnit"];
    renderImp = global["renderImp"];
    makeReachable = global["makeReachable"];

    global["OnPickHex"] = BindJSCallback(&UI::OnPickHex);
    global["OnNextTurn"] = BindJSCallback(&UI::OnNextTurn);
    global["OnRecreate"] = BindJSCallback(&UI::OnRecreate);
    global["OnClearField"] = BindJSCallback(&UI::OnClearField);

    CreateField();
    RenderField();
}

void UI::OnPickHex(const JSObject& obj, const JSArgs& args) {
    Game &game = Game::getGame();
    Field &field = game.getField();

    unsigned x = args[0].ToInteger();
    unsigned y = args[1].ToInteger();

    game.pickCell(Coord(x, y));

    CreateField();
    RenderField();

    vector<shared_ptr<Cell>> paths = game.getCurrentPlayer()->getPaths();
    for(auto &cell : paths)
        makeReachable({ cell->getX(), cell->getY() });
}

void UI::OnNextTurn(const JSObject &obj, const JSArgs &args) {
    Game &game = Game::getGame();
    Field &field = game.getField();

    game.nextTurn();

    CreateField();
    RenderField();
}

void UI::OnRecreate(const JSObject &obj, const JSArgs &args) {
    Game &game = Game::getGame();
    Field &field = game.getField();

    int field_size = args[0].ToInteger();
    if( !(field_size > 0 && field_size <= 35) ) field_size = 25;

    if(field_size != field.getSize())
        game.createField(field_size);

    game.getField().clear();

    game.createImp(Coord(0, 5), "River");
    game.createImp(Coord(5, 5), "Mountains");
    game.createImp(Coord(15, 5), "Forest");
    game.createImp(Coord(15, 15), "Swamp");
    game.createImp(Coord(19, 19), "Rain");
    game.createImp(Coord(2, 18), "Snow");
    game.createImp(Coord(1, 10), "Fog");

    CreateField();
    RenderField();
}

void UI::OnClearField(const JSObject &obj, const JSArgs &args) {
    Game &game = Game::getGame();
    Field &field = game.getField();

    field.clear();
    CreateField();
    RenderField();
}

void UI::CreateField() {
    Game &game = Game::getGame();
    Field &field = game.getField();

    createField({ field.getSize() });

}

void UI::RenderField() {
    Game &game = Game::getGame();
    Field &field = game.getField();

    vector<shared_ptr<Impediment>> &imps = game.getImps();
    vector<shared_ptr<Player>> &players = game.getPlayers();

    for(auto &imp : imps) {
        for(auto &cell : imp->getFilled()) {
            std::string s = imp->getTypeName();
            char imp_type[s.size() + 1];
            strcpy(imp_type, s.c_str());
            renderImp({ cell->getX(), cell->getY(), imp_type });
        }
    }

    for(auto &player : players) {
        for(auto &unit : player->getUnits()) {
            std::string s = unit->getTypeName();
            auto unit_type = stringToChar(s);
            std::string d = player->getColor();
            auto unit_color = stringToChar(d);
            shared_ptr<Cell> position = unit->getPosition();
            renderUnit({ position->getX(), position->getY(), unit_type.get(), unit_color.get() });
        }
    }

}