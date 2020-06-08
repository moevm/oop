#include "Logger.h"


string f() {
	time_t rawtime;
	struct tm* timeinfo;
	string name;

	time(&rawtime);                         // текущая дата, выраженная в секундах
	timeinfo = localtime(&rawtime);   // текущая дата, представленная в нормальной форме
	name = asctime(timeinfo);
	for (int i = 0; i < name.size(); i++) {
		if (name[i] == ' ') name[i] = ' ';
		if (name[i] == ':') name[i] = '-';
	}
	name.pop_back();
	name.push_back('.');
	name.push_back('t');
	name.push_back('x');
	name.push_back('t');
	name.push_back('\0');
	name = "Loggs\\" + name;

	return name;
}
string logger::name = f();
int logger::ForCout = 1;



void logger::set_name() {

	ofstream fout(name);
	fout << name << "\n\n";
	fout.close();
	//cout << name;
}

void logger::add(string s) {
	if (ForCout < 3) file(s);
	if (ForCout > 1) console(s);
}

void logger:: file(string s) {
	ofstream fout(name, ios_base::app);
	fout << s << "";
	fout.close();
}

void logger::console(string s) {
	cout << s;

}