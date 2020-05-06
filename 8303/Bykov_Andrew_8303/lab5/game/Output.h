#include <cstdio>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

class Fwrite {
	ofstream out;
public:
	Fwrite(string filename) {
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

class Fread {
	ifstream in;
public:
	Fread(string filename) {
		in.open(filename);
	}

	stringstream read() {
		stringstream s;
		s << in.rdbuf();
		return s;
	}

	~Fread() {
		in.close();
	}

};