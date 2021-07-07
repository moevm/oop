//
// Created by anton on 12.04.2020.
//

#ifndef OOP_1_FILE_H
#define OOP_1_FILE_H

#include <iostream>
#include <fstream>

class File {
std::ofstream out;
public:
    explicit File(const std::string& fileName)
    {
        out.open(fileName, std::ios::out | std::ios::app);
    }

    ~File()
    {
        out.close();
    }

    void write(std::string& message)
    {
        out << message;
    }
};

#endif //OOP_1_FILE_H
