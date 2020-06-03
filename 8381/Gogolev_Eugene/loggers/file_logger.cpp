#include "file_logger.hpp"

FileLogger::FileLogger (const string& fileName) {
    this->fileName = fileName;
    std::ofstream ofs;
    ofs.open(fileName, std::ofstream::out | std::ofstream::trunc); // Clear file
    ofs.close();
}

void FileLogger::log (const string& message) {
    std::ofstream out;
    out.open(fileName, std::fstream::out | std::fstream::app);
    out << message << endl;
    out.close();
}
