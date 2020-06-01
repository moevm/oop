#include "Logger.h"
#include <ctime>

std::fstream* Logger::_fstream = nullptr;
int Logger::_verboseLevel = 1;
int Logger::_mode = 1;

void Logger::setLoggingMode(int mode) {
	_mode = mode;
}

void Logger::setVerboseLevel(int verbose) {
	_verboseLevel = verbose;
}

void Logger::log(std::string prefix, std::string msg, int verbose) {
	if (_mode == 2 && _fstream == nullptr) {
		_fstream = new std::fstream(LOG_F_NAME, std::ios::out | std::ios::trunc);
	}
	if (verbose <= _verboseLevel) {
		auto tnow = time(0);
		auto ts = localtime(&tnow);
		std::string formattedTimestamp = std::to_string(ts->tm_hour) + ":" + std::to_string(ts->tm_min) + ":" + std::to_string(ts->tm_sec);
		if(_mode > 0)
			qInfo() << (prefix + ": " + msg).c_str();
		if (_mode > 1 && _fstream->good())
			(*_fstream) << (formattedTimestamp + " " + prefix + ": " + msg + "\n");
	}
}