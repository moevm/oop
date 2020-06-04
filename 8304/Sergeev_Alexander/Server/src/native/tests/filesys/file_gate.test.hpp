#ifndef LOGIC_FILESYS_TEST_HPP
#define LOGIC_FILESYS_TEST_HPP

#include "../../base/includes.hpp"
#include "../../filesys/file_gate.hpp"

namespace unit_testing {
    void test_file_gate() {
        std::string file = "my_file.png";

        json j {"PI", 3, 3.14, 3.1415, 3.1415926}, j_new;
        std::string cont = "SAMPLE SaMpLe sample text", cont_new;

        logger::say(l::debug) << "File gate testing started..." << logger::out;
        logger::say() << "Today objects: create file with some content, read it and then delete. Ready?" << logger::out;

        logger::say() << "Creating file with following JSON:" << logger::out;
        logger::say() << j << logger::over;
        file::file_gate::pass(file, j);
        logger::say() << "Reading this file:" << logger::out;
        file::file_gate::pull(file, j_new);
        logger::say() << j_new << logger::over;
        if (j == j_new) logger::say(l::debug) << "Match!" << logger::out;
        else logger::say(l::error) << "No match!" << logger::out;

        logger::say() << "Rewriting file with following string:" << logger::out;
        logger::say() << cont << logger::over;
        file::file_gate::pass(file, cont);
        logger::say() << "Reading this file:" << logger::out;
        file::file_gate::pull(file, cont_new);
        logger::say() << cont_new << logger::over;
        if (cont == cont_new) logger::say(l::debug) << "Match!" << logger::out;
        else logger::say(l::error) << "No match!" << logger::out;

        logger::say() << "Deleting this file" << logger::out;
        file::file_gate::evaporate(file);

        logger::say(l::debug) << "File gate testing finished!" << logger::out;
        logger::say() << logger::over;
    }
}

#endif //LOGIC_FILESYS_TEST_HPP
