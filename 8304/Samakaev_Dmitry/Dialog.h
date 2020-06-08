#pragma once
#include "my_exception.h"
#include <vector>
#include <map>
#include "Fasad.h"
#include "Loggs.h"

class DialogBase
{
protected:
	Fasad* fsd = nullptr;
	std::vector<std::string> commands;

public:
	virtual void start() = 0;
};

class DialogAboutUnits : public DialogBase
{
	LogProxy* log = nullptr;

public:
	DialogAboutUnits(Fasad* fsd, LogProxy* log);
	void start();
	void deleteUnit();
	void relaxUnit();
	void moveUnit();
};


class DialogAboutBase : public DialogBase
{
	std::map<char, std::string> d;
	LogProxy* log = nullptr;

	Unit* decrypt(char c);
public:
	DialogAboutBase(Fasad* fsd, LogProxy* log);
	void start();
	void createUnit();
	void createBase();
	void notifyUnits();
};


class MainDialog : public DialogBase
{
	bool game_is_on = false;
	DialogAboutUnits* undlg;
	DialogAboutBase* bsdlg;
	std::vector<std::string> commands;
	LogProxy* log = nullptr;


public:
	MainDialog(Fasad* fsd);
	void start();
	void startNewGameDialog();
	void saveStateDialog();
	void loadStateDialog();
};

