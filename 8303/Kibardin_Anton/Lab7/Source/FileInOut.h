//
// Created by anton on 12.04.2020.
//

#ifndef OOP_1_FILEINOUT_H
#define OOP_1_FILEINOUT_H

#include <iostream>
#include <fstream>

class FileOut {
std::ofstream out;
public:
    explicit FileOut(const std::string& fileName, std::string mode)
    {
        out.open(fileName);
        puts(fileName.c_str());
        if(mode == "log")
            out.open(fileName, std::ios::out | std::ios::app);
        else
            out.open(fileName, std::ios::out);
    }

    ~FileOut()
    {
        out.close();
    }

    void write(std::string message)
    {
        out << message;
    }
};

class FileIn {
    std::ifstream in;
public:
    explicit FileIn(const std::string& fileName)
    {
        in.open(fileName, std::ios::in);
    }

    ~FileIn()
    {
        in.close();
    }

    std::string read()
    {
        std::string str;
        in >> str;
        return str;
    }
};
#endif //OOP_1_FILEINOUT_H
