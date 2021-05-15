    #ifndef FILEWRITE_H
#define FILEWRITE_H

#include <cstdio>
#include <iostream>
#include <sstream>
#include <fstream>

class FileRAII { // RAII
    std::ofstream out;
public:
    FileRAII(const std::string &filename, std::string opt){
        if(opt == "log") //дозапись уже созданного файла с логами
            out.open(filename, std::ios::app | std::ios::out);
        else
            out.open(filename);
    }

    ~FileRAII(){
        out.close();
    }

    void write(std::string data) {
        out << data << std::endl;
    }
};

class FileRead {
    std::ifstream in;
public:
    FileRead (std::string filename)  {
        in.open(filename);
    }

    ~FileRead() {
        in.close();
    }

    std::stringstream read() {
        std::string s;
        std::stringstream strStream;
        strStream << in.rdbuf();
        return strStream;
    }

};

#endif // FILEWRITE_H
