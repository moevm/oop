#pragma once
#include <fstream>
#include <string>
#include <QDebug>

#define LOG_F_NAME "log.txt" //макрос, куда записываем лог

//три стат. метода
class Logger
{
public:
	static void setLoggingMode(int mode);	//куда записываем, 0 - никуда, 1 - в консоль, 2 - to console & to file
	static void setVerboseLevel(int verbose);	//метод, verbose - на сколько подробно все будет записываться(уровень важности), есть также 3 уровня
	static void log(std::string prefix, std::string msg, int verbose = 3);//приним. в себя, какой уровень хочу записать
	//префикс - чтобы понять, откуда у нас сообщение пришло, само сообщение и важность сообения
protected:
	static int _mode;
	static int _verboseLevel;
	static std::fstream* _fstream;
};

//allow фильтровать комментарий, которые не нужны в данный момент