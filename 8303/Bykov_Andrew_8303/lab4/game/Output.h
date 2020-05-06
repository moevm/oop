#include <cstdio>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

class Fwrite {
	ofstream out;
public:
	Fwrite(const string& filename) {
		out.open(filename);
	}
	void write(string data) {
		out << data << endl;
	}
	~Fwrite()
	{
		out.close();
	}

};
