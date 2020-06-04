#include "file_gate.hpp"
//#include <experimental/filesystem>

#if defined(_WIN32)
#include <direct.h>
#else
#include <sys/types.h> // required for stat.h
#include <sys/stat.h> // no clue why required -- man pages say so
#endif


std::string file::file_gate::ROOT;

const std::string file::file_gate::p_general = "general/";
const std::string file::file_gate::p_saves = "saves/";
const std::string file::file_gate::p_logs = "logs/";



void file::file_gate::pass(std::string& file_name, std::string& contents, file::modes mode, folders dir) {
    std::string absolute;
    get_path(absolute, dir, file_name);
    std::fstream::openmode modus = get_mode(mode);

    std::ofstream out;
    out.open(absolute, std::fstream::out | modus);
    out << contents;
    out.flush();
    out.close();
}

void file::file_gate::pass(std::string &file_name, json &contents, file::modes mode, file::folders dir) {
    std::string absolute;
    get_path(absolute, dir, file_name);
    std::fstream::openmode modus = get_mode(mode);

    std::ofstream out;
    out.open(absolute, std::fstream::out | modus);
    out << contents;
    out.flush();
    out.close();
}



void file::file_gate::pull(std::string &file_name, std::string &container, file::folders dir) {
    std::string absolute;
    get_path(absolute, dir, file_name);

    std::ifstream in;
    in.open(absolute, std::fstream::in);
    container.assign(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
    in.close();
}

void file::file_gate::pull(std::string &file_name, json &container, file::folders dir) {
    std::string absolute;
    get_path(absolute, dir, file_name);

    std::ifstream in;
    in.open(absolute, std::fstream::in);
    in >> container;
    in.close();
}



void file::file_gate::evaporate(std::string &file_name, file::folders dir) {
    std::string absolute;
    get_path(absolute, dir, file_name);

    if (remove(absolute.c_str()) != 0)
        logger::say() << "Error deleting: " << absolute << logger::out;
    else
        logger::say() << "File: " << absolute << " deleted successfully." << logger::out;
}



void file::file_gate::get_path(std::string& target, folders dir, std::string& file_name) {
    target += ROOT;
    switch (dir) {
        case general:
            target += p_general;
            break;
        case saves:
            target += p_saves;
            break;
        case logs:
            target += p_logs;
            break;
    }
    prove_path(target);
    target += file_name;
}

std::fstream::openmode file::file_gate::get_mode(file::modes mode) {
    switch (mode) {
        case rewrite:
            return std::fstream::trunc;
        case append:
            return std::fstream::app;
    }
    return std::fstream::trunc;
}



void file::file_gate::prove_path(std::string& path) {
    /*namespace fs = std::experimental::filesystem;
    if (!fs::is_directory(path) || !fs::exists(path)) {
        fs::create_directory(path);
    }*/
    #if defined(_WIN32)
        mkdir(path.c_str()); // can be used on Windows
    #else
        mode_t nMode = 0733; // UNIX style permissions
        mkdir(path.c_str(), nMode); // can be used on non-Windows
    #endif
}
