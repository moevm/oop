#include <string>
#include <fstream>
using namespace std;

class LogFileHandler
{
public:

    string path;
    ofstream log;
    LogFileHandler(string Path) : path(Path)
    {
        log.open(Path);
        log << ios_base::app;
    }

    ~LogFileHandler()
    {
        log.close();
    }
};

class Logger
{
public:

    string path;

    Logger(string Path) : path(Path) {};

    void placeHQLog( string faction, int x, int y )
    {
        LogFileHandler lfh(path);
        lfh.log << "Player " << faction << " placed their HQ at (" << x << ", " << y << ")\n";
    };
    void moveLog( string name, string faction, int dx, int dy)
    {
        LogFileHandler lfh(path);
        lfh.log << "Unit " << name << " [" << faction << "] moved by (" << dx << ", " << dy << ")\n";
    };
    void attackLog( string aName, string aFaction, string tName, string tFaction)
    {
        LogFileHandler lfh(path);
        lfh.log <<  aName << " [" << aFaction << "] attacked " <<  tName << " [" << tFaction << "]\n";
    };
    void buyLog( string faction, string name, int price)
    {
        LogFileHandler lfh(path);
        lfh.log << "Player " << faction << " bought " << name << " for " << price << "\n";
    };
    void HQAddUnitLog( string faction, string name)
    {
        LogFileHandler lfh(path);
        lfh.log << faction << " got " << name << "\n";
    };
    void HQLoseUnitLog( string faction, string name)
    {
        LogFileHandler lfh(path);
        lfh.log << faction << " lost " << name << "\n";
    };
};
