#ifndef FILE_H
#define FILE_H
#include <iostream>
#include <fstream>
class File
{
    std::ofstream out;
    bool isOpen;
public:
    File(const std::string& fileName):isOpen(true)
    {
        out.open(fileName);
    }

    void write(std::string str)
    {
        out << str;
    }

    /*std::string read()
    {
        char str[1000] = "";
        if (fgets(str, 1000, out) == NULL)
        {
            return str;
        }
        std::string result_str(str);
        return result_str;
    }*/

    bool checkOpen()
    {
        return isOpen;
    }

    ~File()
    {
       out.close();
    }
};



#endif // FILE_H
