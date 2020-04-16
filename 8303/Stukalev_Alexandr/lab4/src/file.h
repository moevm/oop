#ifndef FILE_H
#define FILE_H
#include <iostream>
class File
{
    std::FILE* file;
    bool isOpen;
public:
    File(char* filename):isOpen(true)
        {
            this->file = std::fopen(filename, "w+");
            if (!file)
                return;
        }
    void write(const char* str)
        {
            if (std::fputs(str, file) == EOF)
                return;
        }
    bool checkOpen()
    {
        return isOpen;
    }
    ~File()
        {
            std::fclose(file);
        }
};



#endif // FILE_H
