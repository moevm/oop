#include "Dialog.h"

MainDialog::MainDialog(Fasad* fsd)
{
	int k;
	std::cout << "Choose log type:\n1) File\n2) Terminal\nAny other number - no log\n";
	std::cin >> k;
	std::cout << "\n";

	switch (k)
	{
	case 1:
		log = new LogProxy(LogTypes::File);
		break;
	case 2:
		log = new LogProxy(LogTypes::Terminal);
		break;
	default:
		log = new LogProxy(LogTypes::No);
		break;
	}

	this->fsd = fsd;
	undlg = new DialogAboutUnits(fsd, log);
	bsdlg = new DialogAboutBase(fsd, log);

	commands.push_back("1) Work with base");
	commands.push_back("2) Work with units");
	commands.push_back("3) Show field");
	commands.push_back("4) Show log");
	commands.push_back("5) Save state");
	commands.push_back("6) Load state");
	commands.push_back("7) Start new game");
	commands.push_back("8) Quit");
}

void MainDialog::start()
{
	size_t count_turns = 0;
	while (true)
	{
		if(this->game_is_on)
			std::cout << "Player number " << count_turns % 2 + 1<<", it's your turn\n";
		std::cout << "Choose:\n";
		for (auto& command : commands)
			std::cout << command << "\n";

		char n;
		std::cin >> n;
		std::cout << "\n";

		switch (n)
		{
		case '1':
			bsdlg->start();
			count_turns++;
			break;
		case '2':
			undlg->start();
			count_turns++;
			break;
		case '3':
			fsd->printFld();
			break;
		case '4':
			log->show();
			break;
		case '5':
			saveStateDialog();
			break;
		case '6':
			loadStateDialog();
			break;
		case '7':
			startNewGameDialog();
			break;
		case '8':
			return;
		default:
			break;
		}
	}
}

void MainDialog::saveStateDialog()
{
	fsd->saveState()->write();
	std::cout << "State saved\n";
}

void MainDialog::startNewGameDialog()
{
	std::cout << "New game started, two bases are in upper left and lower right corners\n";
	fsd->createBase(0, 0);
	fsd->createBase(9, 9);
	this->game_is_on = true;

}

void MainDialog::loadStateDialog()
{
	std::string data;
	
	std::ifstream in("save.txt");
	if (in.is_open() == 0)
	{
		std::cout << "No input file\n";
		return;
	}
	in >> data;

	bool res = fsd->loadState(new Field::Snapshot(data));
	if (res == true)
	{
		std::cout << "State loaded\n";
		return;
	}
	std::cout << "Input file is changed\n";
}

DialogAboutUnits::DialogAboutUnits(Fasad* fsd, LogProxy* log)
{
	this->fsd = fsd;
	this->log = log;

	commands.push_back("1) Delete");
	commands.push_back("2) Relax (+ 20 hp)");
	commands.push_back("3) Move");
}

void DialogAboutUnits::start()
{
	std::cout << "Choose command to unit:\n";
	for (auto& command : commands)
		std::cout << command << "\n";

	int n;
	std::cin >> n;
	std::cout << "\n";

	switch (n)
	{
	case 1:
		deleteUnit();
		break;
	case 2:
		relaxUnit();
		break;
	case 3:
		moveUnit();
		break;
	default:
		break;
	}
}

void DialogAboutUnits::deleteUnit()
{
	int x, y;
	std::cout << "Enter corrdinates:\n";
	std::cin >> x >> y;
	std::cout << "\n";

	auto res = fsd->deleteUnit(x, y);

	try {
		if (res == false)
			throw my_exception("Incorrect data!");
	}
	catch (my_exception & e) {
		std::cout << e.what() << std::endl;
		return;
	}

	std::cout << "Unit deleted\n";
	log->writeAboutUnitRemoving(x, y);

}

void DialogAboutUnits::relaxUnit()
{
	int x, y;
	std::cout << "Enter corrdinates:\n";
	std::cin >> x >> y;
	std::cout << "\n";

	auto res = fsd->relaxUnit(x, y);
	try {
		if (res == false)
			throw my_exception("Incorrect coordinates\n");
		
	}
	catch (my_exception & e) {
		std::cout << e.what() << std::endl;
		return;
	}

	std::cout << "Unit relaxed\n";
}

void DialogAboutUnits::moveUnit()
{
	int x_from, y_from;
	std::cout << "Enter coordinates from: ";
	std::cin >> x_from >> y_from;
	std::cout << "\n";

	int x_to, y_to;
	std::cout << "Enter coordinates to: ";
	std::cin >> x_to >> y_to;
	std::cout << "\n";

	auto res = fsd->moveUnit(x_from, y_from, x_to, y_to);

	switch (res)
	{
	case MovingUnitResult::IncorrectCoordinates:
		std::cout << "Incorrect coordinates\n";
		break;
	case MovingUnitResult::NoUnit:
		std::cout << "No unit\n";
		break;
	case MovingUnitResult::Colission:
		std::cout << "Colission\n";
		break;
	case MovingUnitResult::Ok:
		std::cout << "Unit moved\n";
		log->writeAboutUnitMoving(x_from, y_from, x_to, y_to);
		break;
	default:
		break;
	}
}

DialogAboutBase::DialogAboutBase(Fasad* fsd, LogProxy* log)
{
	this->fsd = fsd;
	this->log = log;

	commands.push_back("1) Create base");
	commands.push_back("2) Create unit in chosen base");
	commands.push_back("3) Use base-boost");

	d['T'] = "Siedge tower";
	d['C'] = "Catapult";
	d['A'] = "Archer";
	d['M'] = "Mage";
	d['K'] = "Knight";
	d['R'] = "Rogue";
}

void DialogAboutBase::start()
{
	std::cout << "Choose command to unit:\n";
	for (auto& command : commands)
		std::cout << command << "\n";

	int n;
	std::cin >> n;
	std::cout << "\n";

	switch (n)
	{
	case 1:
		createBase();
		break;
	case 2:
		createUnit();
		break;
	case 3:
		notifyUnits();
		break;
	default:
		break;
	}
}

void DialogAboutBase::createUnit()
{
	int x, y;
	std::cout << "Enter base corrdinates:\n";
	std::cin >> x >> y;
	std::cout << "\n";

	char c;
	std::cout << "Choose unit type:\n";
	for (auto& type : d)
		std::cout << type.first << " - " << type.second << "\n";
	std::cin >> c;
	std::cout << "\n";

	Unit* unit = decrypt(c);
	try {
		if (unit == nullptr)
			throw my_exception("Incorrect type\n");
	}
	catch(my_exception & e) {
		std::cout << e.what() << std::endl;
		return;
	}

	auto res = fsd->createUnit(x, y, unit);

	switch (res)
	{
	case CreatingUnitResult::IncorrectCoordinates:
		std::cout << "Incorrect coordinates\n";
		break;
	case CreatingUnitResult::Collision:
		std::cout << "Colission\n";
		break;
	case CreatingUnitResult::noBase:
		std::cout << "No base\n";
		break;
	case CreatingUnitResult::Ok:
		std::cout << "Unit added\n";
		log->writeAboutUnitCreating(x, y, d[unit->name]);
		break;
	}
}

Unit* DialogAboutBase::decrypt(char c)
{
	Unit* unit;

	switch (c)
	{
	case 'T':
		unit = new Siege_tower;
		break;
	case 'C':
		unit = new Catapult;
		break;
	case 'A':
		unit = new Archer;
		break;
	case 'M':
		unit = new Mage;
		break;
	case 'K':
		unit = new Knight;
		break;
	case 'R':
		unit = new Rogue;
		break;
	default:
		unit = nullptr;
		break;
	}

	return unit;
}

void DialogAboutBase::createBase()
{
	int x, y;
	std::cout << "Enter base corrdinates:\n";
	std::cin >> x >> y;
	std::cout << "\n";

	auto res = fsd->createBase(x, y);

	switch (res)
	{
	case CreatingBaseResult::IncorrectCoordinates:
		std::cout << "Incorrect coordinates\n";
		break;
	case CreatingBaseResult::Collision:
		std::cout << "Colission\n";
		break;
	case CreatingBaseResult::Ok:
		std::cout << "Base created\n";
		log->writeAboutBaseCreating(x, y);
		break;
	default:
		break;
	}
}

void DialogAboutBase::notifyUnits()
{
	int x, y;
	std::cout << "Enter base corrdinates:\n";
	std::cin >> x >> y;
	std::cout << "\n";

	auto res = fsd->notifyBase(x, y);

	if (res == false)
	{
		std::cout << "Incorrect coordinates\n";
		return;
	}

	std::cout << "Units notified\n";
}
