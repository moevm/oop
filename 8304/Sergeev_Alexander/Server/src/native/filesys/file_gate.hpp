#ifndef LOGIC_FILE_GATE_HPP
#define LOGIC_FILE_GATE_HPP

#include "../base/includes.hpp"


namespace file {
    enum modes {
        rewrite, append
    };

    enum folders : char {
        general = 'G', saves = 'S', logs = 'L'
    };



    class file_gate {
    public:
        static std::string ROOT;

        static void pass(std::string& file_name, std::string& contents, modes mode = rewrite, folders dir = general);
        static void pass(std::string& file_name, json& contents, modes mode = rewrite, folders dir = general);

        static void pull(std::string& file_name, std::string& container, folders dir = general);
        static void pull(std::string& file_name, json& container, folders dir = general);

        static void evaporate(std::string& file_name, folders dir = general);

    private:
        static const std::string p_general;
        static const std::string p_saves;
        static const std::string p_logs;

        static void get_path(std::string& target, folders dir, std::string& file_name);
        static std::fstream::openmode get_mode(modes mode);

        static void prove_path(std::string& path);
    };
}

#endif //LOGIC_FILE_GATE_HPP
