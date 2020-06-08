#pragma once
#include <string>
#include <fstream>

class Snapshot
{

	std::string data;

public:
	Snapshot(std::string& data);
	void write();
};

