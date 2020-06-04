#include "errors.hpp"
#include "includes.hpp"

const char *basic_exception::what() const noexcept {
    std::cout << "!!!" << info << "!!!" << std::endl;
    return info.c_str();
}

basic_exception::basic_exception(const std::string &msg) { }

void basic_exception::log() {
    logger::enable_all(false);
    logger::enable_logger(true, l::server_console_logger);
    logger::say(info, l::error);
    logger::enable_all(true);
}

void basic_exception::pass() {
    // Actually really do nothing. Do not give a shit about the exception.
}



shared_pointer_exception::shared_pointer_exception(const std::string &msg) : basic_exception(msg) {
    this->info = "[Shared pointer exception] " + msg;
    log();
}

serialization_exception::serialization_exception(const std::string &msg) : basic_exception(msg) {
    this->info = "[Serialization exception] " + msg;
    log();
}

deserialization_exception::deserialization_exception(const std::string &msg) : basic_exception(msg) {
    this->info = "[Deserialization exception] " + msg;
    log();
}

unimplemented_exception::unimplemented_exception(const std::string &msg) : basic_exception(msg) {
    this->info = "[Unimplemented exception] " + msg;
    log();
}

recursion_exception::recursion_exception(const std::string &msg) : basic_exception(msg) {
    this->info = "[Recursion exception] " + msg;
    log();
}

null_pointer_exception::null_pointer_exception(const std::string &msg) : basic_exception(msg) {
    this->info = "[Null pointer exception] " + msg;
    log();
}

out_of_bounds_exception::out_of_bounds_exception(const std::string &msg) : basic_exception(msg) {
    this->info = "[Out of bounds exception] " + msg;
    log();
}

conflict_exception::conflict_exception(const std::string &msg) : basic_exception(msg) {
    this->info = "[Conflict bounds exception] " + msg;
    log();
}

rights_exception::rights_exception(const std::string &msg) : basic_exception(msg) {
    this->info = "[Rights exception] " + msg;
    log();
}

type_exception::type_exception(const std::string &msg) : basic_exception(msg) {
    this->info = "[Type exception] " + msg;
    log();
}
