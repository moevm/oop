#ifndef FILEWRITE_H
#define FILEWRITE_H

#include <cstdio>
#include <iostream>
#include <sstream>
#include <fstream>

class FileRAII { // RAII
    std::ofstream out;
public:
    FileRAII(const std::string &filename){
         out.open(filename);
    }

    ~FileRAII(){
        out.close();
    }

    void write(std::string data) {
        out << data << std::endl;
    }
};

#endif // FILEWRITE_H
