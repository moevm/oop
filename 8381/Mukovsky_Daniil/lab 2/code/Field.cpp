#include "Field.h"

PlayingField::Cell::Cell()
{
	fieldObject_ = nullptr;
	landscape = nullptr;
}

PlayingField::Cell::Cell(const Cell& copyCell) {
	FieldObject* newObject = (copyCell.fieldObject_)->copy();
	fieldObject_ = newObject;

	Landscape* copyLand = (copyCell.landscape)->copy();
	landscape = copyLand;

}

PlayingField::Cell::Cell(Cell&& copyCell)noexcept {
	fieldObject_ = copyCell.fieldObject_;
	landscape = copyCell.landscape;
	
	copyCell.fieldObject_ = nullptr;
	copyCell.landscape = nullptr;
}

PlayingField::Cell& PlayingField::Cell::operator=(Cell&& copyCell) noexcept
{
	if (&copyCell == this)
		return *this;
	fieldObject_ = copyCell.fieldObject_;
	landscape = copyCell.landscape;
	copyCell.fieldObject_ = nullptr;
	copyCell.landscape = nullptr;
	return *this;
}

PlayingField::Cell& PlayingField::Cell::operator=(const Cell& copyCell)
{
	if (&copyCell == this)
		return *this;
	if (copyCell.fieldObject_) 
	{
		FieldObject* newObject = (copyCell.fieldObject_)->copy();
		fieldObject_ = newObject;
	}
	else fieldObject_ = nullptr;
	
	if (copyCell.landscape)
	{
		Landscape* copyLand = (copyCell.landscape)->copy();
		landscape = copyLand;
	}
	else landscape = nullptr;

	return *this;
}

bool PlayingField::Cell::isOccupied() {
	if (fieldObject_/*&& other objects*/) {
		//std::cout << "Cell is occupied\n";
		return true;
	}
	return false;
}

FieldObject* PlayingField::Cell::getObjectPtr()
{
	return fieldObject_;
}

void PlayingField::Cell::setObjectPtr(FieldObject* newObjectPtr)
{
	fieldObject_ = newObjectPtr;
}

void PlayingField::setMaxNumberOfElements(int newValue)
{
	if (newValue < currentNumberOfElements){
		std::cout << "Field:You cannot set this value for maximum field elements: there are already more units on the field\n";
		return;
	}
	if (width * length >= newValue)
		maxNumberOfElements = newValue;
	else 
		std::cout << "Field:You cannot set this value for maximum field elements: the field size is less than the number of units\n";
}


PlayingField::PlayingField(int width_, int length_) : width(width_), length(length_)
{
	maxNumberOfElements = width*length;
	currentNumberOfElements = 0;
	field = nullptr;
	if (width < 1 || length < 1)
	{
		std::cout << "Field:Incorrect field size!\n";
		return;
	}
	field = new Cell * [width];
	for (int i = 0; i < width; i++)
	{
		field[i] = new Cell[length];
	}

	setRandomLandscape();

	std::cout << "[field]Constructor\n";
}


PlayingField::PlayingField(const PlayingField& copyField) : width(copyField.width), length(copyField.length), currentNumberOfElements(copyField.currentNumberOfElements), maxNumberOfElements(copyField.maxNumberOfElements)
{
	field = new Cell * [width];
	for (int i = 0; i < width; i++)
	{
		field[i] = new Cell[length];
		for (int j = 0; j < length; j++)
		{
			field[i][j] = copyField.field[i][j];
		}
	}
	std::cout << "[field]Copy constructor is called\n";
}

PlayingField::PlayingField(PlayingField&& copyField)noexcept : width(copyField.width), length(copyField.length), currentNumberOfElements(copyField.currentNumberOfElements), maxNumberOfElements(copyField.maxNumberOfElements)
{
	field = copyField.field;
	copyField.field = nullptr;
	std::cout << "[field]Move constructor is called\n";
}


PlayingField& PlayingField::operator=(const PlayingField& playingField)
{
	std::cout << "[field]Assignment(copy) operator is called\n";
	if (this != &playingField) 
	{
		for (int i = 0; i < width; i++)
			delete[] field[i];
		delete[] field;
		width = playingField.width;
		length = playingField.length;
		currentNumberOfElements = playingField.currentNumberOfElements;
		maxNumberOfElements = playingField.maxNumberOfElements;
		field = new Cell* [width];
		for (int i = 0; i < width; i++)
		{
			field[i] = new Cell [length];
			for (int j = 0; j < length; j++)
				field[i][j] = playingField.field[i][j];
		}
	}
	return *this;
}

PlayingField& PlayingField::operator=(PlayingField&& playingField) noexcept
{
	std::cout << "[field]Assignment(move) operator is called\n";
	if (this != &playingField)
	{
		for (int i = 0; i < width; i++)
			delete[] field[i];
		delete[] field;
		width = playingField.width;
		length = playingField.length;
		currentNumberOfElements = playingField.currentNumberOfElements;
		maxNumberOfElements = playingField.maxNumberOfElements;
		field = playingField.field;
		playingField.field = nullptr;
	}
	return *this;
}
PlayingField::~PlayingField() {
	std::cout << "[field]Destructor\n";
	if (!field) return;
	for (int i = 0; i < width; i++)
		delete[] field[i];
	delete[] field;
}

int PlayingField::getCurrentElements() {
	return currentNumberOfElements;
}

bool PlayingField::addObject(FieldObject* newObject, int X , int Y ) {
	if (maxNumberOfElements == currentNumberOfElements)
	{
		std::cout << "Field:Can't add more Objects \n";
		return false;
	}
	int i = 0, j = 0;

	if (X == -1 && Y == -1) {
		int flag = false;
		for (i = 0; i < width; i++)
		{
			for (j = 0; j < length; j++)
			{
				if (!field[i][j].isOccupied())
				{
					std::cout << "Field:Object added X:"<<j<<" Y:"<<i<<"\n";
					field[i][j].setObjectPtr(newObject);   
					currentNumberOfElements++;
					flag = true;
					break;
				}
			}
			if (flag) return false;
		}
	}
	else {
		if (!checkCoordinate(X, Y)) {
			return false;
		}
		if (field[Y][X].isOccupied()) {
			std::cout << "Field: Cell with coordinates X:" << X << " Y:" << Y << " is occupied, can't add object\n";
			return false;
		}
		field[Y][X].setObjectPtr(newObject);
		std::cout << "Field:Object added X:" << X << " Y:" << Y << "\n";
	}
	return true;
}


void PlayingField::showConsoleField() {
	std::string name;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < length; j++) {
			if (field[i][j].getObjectPtr()) {
				name = field[i][j].getObjectPtr()->getShortName();
				std::cout <<"["<< name<<"]";
			}
			else
				std::cout << "[___]";
		}
		std::cout << "\n";
	}
}
void PlayingField::showConsoleLandscape() {
	std::string name;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < length; j++) {
			name = field[i][j].getLandscapePtr()->getShortName();
			std::cout << "[_"<<name<<"_]";
		}
		std::cout << "\n";
	}
}
bool PlayingField::checkCoordinate(int x, int y) const
{
	if (x >= length || x < 0 || y >= width || y < 0) {
		std::cout << "Field:Point goes beyond the field boundaries\n";
		return false;
	}
	return true;
}



void PlayingField::moveObject(int X_old, int Y_old, int X_new, int Y_new) {
	if (checkCoordinate(X_old,Y_old)&&checkCoordinate(X_new,Y_new))

		if (!field[Y_new][X_new].getObjectPtr()) {
			if (field[Y_old][X_old].getObjectPtr()) {
				field[Y_new][X_new].setObjectPtr(field[Y_old][X_old].getObjectPtr());
				field[Y_old][X_old].setObjectPtr(nullptr);
				std::cout << "Field:Unit mooved from X:"<<X_old<<" Y:"<<Y_old<<"  to X:"<<X_new<<" Y:"<<Y_new<<"\n";
			}
			else {
				std::cout << "[moveUnit]No unit, X:" << X_old << " Y:" << Y_old << "\n";
				return;
			}
		}
		else
			std::cout << "[moveUnit]cell is occupied, X:" << X_new << " Y:" << Y_new << "\n";
	
}



void PlayingField::deleteObject(int X, int Y) {
	if (checkCoordinate(X,Y))
		if (field[Y][X].getObjectPtr()) {
			delete field[X][Y].getObjectPtr();
			field[Y][X].setObjectPtr(nullptr);
			currentNumberOfElements--;
			std::cout << "Field:Unit deleted X:" << X << " Y:" << Y << "\n";
		}
		else 
			std::cout << "[deleteUnit]No unit, X:" << X << " Y:" << Y << "\n";
}
void PlayingField::deleteObject(FieldObject* obj) {
	if (!obj) {
		return;
	}
	Coord c = findObjectCoordinates(obj);
	deleteObject(c.x,c.y);
}

void PlayingField::setRandomLandscape() {
	srand(time(0));
	for (unsigned int i = 0; i < width; i++) {
		for (unsigned int j = 0; j < length; j++) {
			int random_land = rand() % 3+0;
			switch (random_land) {
			case(ground): {
				field[i][j].setLandscapePtr(new LandscapeProxy(new Ground));
				break;
			}
			case(water): {
				field[i][j].setLandscapePtr(new LandscapeProxy(new Water));
				break;
			}
			case(mountain): {
				field[i][j].setLandscapePtr(new LandscapeProxy(new Mountains));
				break;
			}
			}
		}
	}
}


void PlayingField::setLandscape(std::vector<char> map) {
	if (map.size() < width * length) {
		std::cout << "Field:Can't set new landscape, new map is smaller than field size\n";
		return;
	}
	int c = 0;
	for (unsigned int i = 0; i < width; i++) {
		for (unsigned int j = 0; j < length; j++) {
			switch (map[c]) {
			case('G'): {
				field[i][j].setLandscapePtr(new LandscapeProxy(new Ground));
				break;
			}
			case('W'): {
				field[i][j].setLandscapePtr(new LandscapeProxy(new Water));
				break;
			}
			case('M'): {
				field[i][j].setLandscapePtr(new LandscapeProxy(new Mountains));
				break;
			}
			}
			c++;
		}
	}
}