#ifndef INFILE_H
#define INFILE_H

#include <iostream>
#include <fstream>
class Filein
{
    std::ifstream out;
    bool isOpen;
public:
    Filein(const std::string& fileName):isOpen(true)
    {
        out.open(fileName);
    }


    std::string read()
    {
        std::string s = "";
        getline(out, s, '!');
        return s;
    }

    bool checkOpen()
    {
        return isOpen;
    }

    ~Filein()
    {
       out.close();
    }
};
#endif // INFILE_H
