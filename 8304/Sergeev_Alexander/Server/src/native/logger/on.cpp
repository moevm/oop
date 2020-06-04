#include "on.hpp"

l::on::on () : utils::singleton<on>() {
    stream = message;
    logs = new abstract_logger*[4];
    logs[server_console_logger] = new logger_server();
    logs[broadcast_logger] = new logger_broadcast();
    logs[server_file_logger] = new logger_file();
    logs[user_logger] = new logger_user();
    alpha = std::ostringstream();
}

l::on::~on () {
    delete logs[server_console_logger];
    delete logs[broadcast_logger];
    delete logs[server_file_logger];
    delete logs[user_logger];
    delete[] logs;
}

void l::on::enable_logger(bool enabled, l::loggers logger) {
    utils::singleton<on>::get().logs[logger]->set_enabled(enabled);
}

void l::on::enable_all(bool enabled) {
    on& fin = utils::singleton<on>::get();
    fin.logs[server_console_logger]->set_enabled(enabled);
    fin.logs[broadcast_logger]->set_enabled(enabled);
    fin.logs[server_file_logger]->set_enabled(enabled);
    fin.logs[user_logger]->set_enabled(enabled);
}

void l::on::send (bool decorated) {
    std::string verbal = this->alpha.str();
    if (logs[server_console_logger]->is_enabled())
        logs[server_console_logger]->let(verbal, stream, decorated);
    if (logs[broadcast_logger]->is_enabled())
        logs[broadcast_logger]->let(verbal, stream, decorated);
    if (logs[server_file_logger]->is_enabled())
        logs[server_file_logger]->let(verbal, stream, decorated);
    if (logs[user_logger]->is_enabled())
        logs[user_logger]->let(verbal, stream, decorated);
    alpha = std::ostringstream();
}

l::on& l::on::say (streams str) {
    on& fin = utils::singleton<on>::get();
    fin.stream = str;
    return fin;
}

void l::on::say (json &object, l::streams str) {
    on& fin = utils::singleton<on>::get();
    fin.stream = str;
    fin.alpha << object.dump(4);
    fin.send(true);
}

namespace l {
    l::on& operator<<(l::on &out, json &object) {
        out.alpha << object.dump(4);
        return out;
    }

    l::on& operator<<(l::on &out, l::on &(*f)(l::on &)) {
        return f(out);
    }

    void operator<<(l::on &out, void (*f)(l::on &)) {
        f(out);
    }
}


l::on& l::on::over (on& out) {
    out.send(false);
    return out;
}

void l::on::out (on& out) {
    out.send(true);
}
