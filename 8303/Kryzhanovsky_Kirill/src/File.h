//
// Created by therealyou on 31.05.2020.
//

#ifndef LAB1_FILE_H
#define LAB1_FILE_H

#include <iostream>
#include <fstream>

class File {
    std::ofstream out;
public:
    explicit File(const std::string &fileName) {
        out.open(fileName, std::ios::out | std::ios::app);
    }

    ~File() {
        out.close();
    }

    void write(std::string &message) {
        out << message;
    }
};

#endif //LAB1_FILE_H
