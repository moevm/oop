#include "Snapshot.h"

Snapshot::Snapshot(std::string& data) : data(data)
{}

void Snapshot::write()
{
	std::ofstream out("save.txt");

	out << data;
	out.close();
}
