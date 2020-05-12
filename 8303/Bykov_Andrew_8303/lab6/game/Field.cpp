#include "Field.h"
#include "Base.h"
#include "Adapter.h"
#include <fstream>

Field::Field(int w, int h, Adapter * a) : width(w), height(h), max_units(w*h/2), adapter(a)
{
	curFrame = 0;
	cells = new Cell*[height];
	for (int i = 0; i < height; i++) cells[i] = new Cell[width];
		
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			cells[i][j].unit = new EmptyUnit();
			cells[i][j].land = new MeadowProxy();
			cells[i][j].netral = new EmptyObject();
		}
	

	cells[0][0].land = new BuildingProxy();
	cells[0][1].land = new BuildingProxy();
	cells[1][0].land = new BuildingProxy();
	cells[1][1].land = new BuildingProxy();

	cells[height - 1][width - 1].land = new BuildingProxy();
	cells[height - 2][width - 1].land = new BuildingProxy();
	cells[height - 1][width - 2].land = new BuildingProxy();
	cells[height - 2][width - 2].land = new BuildingProxy();


	base.water = new WaterBase(Point(0, 0), Point(2, 2), this, adapter);
	base.fire = new FireBase(Point(width - 1, height - 1), Point(width - 3, height - 3), this, adapter);

}
Field& Field::operator=(const Field &field) 
{
	cells = new Cell*[height];
	for (int i = 0; i < height; i++) cells[i] = new Cell[width];
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			cells[i][j] = field.cells[i][j];
		}
	return *this;
}
Field::Field(Field &&field) : width(field.width), height(field.height), max_units(width * height / 2)
{
	cells = new Cell*[height];
	for (int i = 0; i < height; i++) cells[i] = new Cell[width];
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cells[i][j] = field.cells[i][j];
			
		}
		delete(field.cells[i]);
	}
	delete(field.cells);
}

void Field::paint(sf::RenderWindow * window, float frame) 
{
	curFrame += frame * 0.005f;
	if (curFrame > 3) curFrame -= 3;
	for (int i = 0; i < width - 1; i++)
	{
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(i * 50.0f + 50, 0.0f)),
			sf::Vertex(sf::Vector2f(i * 50.0f + 50, height * 70.0f - 1))
		}; line->color = sf::Color::Black;
		window->draw(line, 2, sf::Lines);
	}
	for (int i = 0; i < height - 1; i++)
	{
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(0.0f, i * 70.0f + 70)),
			sf::Vertex(sf::Vector2f(width * 50.0f - 1, i * 70.0f + 70))
		};
		line->color = sf::Color::Black;
		window->draw(line, 2, sf::Lines);
	}
	
	sf::Sprite sprite;
	sf::Texture tileSet;
	sf::Font font;
	sf::Text text;
	TextureFactory * f = new TextureFactory();
	text.setFont(font);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);
	text.setCharacterSize(12);
	font.loadFromFile("arial.ttf");

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (cells[i][j].land->sprite != "Meadow")
			{
				sprite = f->getTexture(cells[i][j].land)->sprite;
				sprite.setPosition(j * 50.0f, i * 70.0f);
				window->draw(sprite);
			}

			if (cells[i][j].unit->isAttack == 0)
				sprite = cells[i][j].unit->getSprite(0);
			else { sprite = cells[i][j].unit->getSprite(curFrame); cells[i][j].unit->isAttack--; }
			sprite.setPosition(j * 50.0f, i * 70.0f);

			if (cells[i][j].unit->isAttacked)
			{
				sprite.setColor(sf::Color::Red);
				cells[i][j].unit->isAttacked--;
			}
			else sprite.setColor(sf::Color::White);

			window->draw(sprite);

			if (cells[i][j].unit->getNumber())
			{
				text.setString("(" + to_string(cells[i][j].unit->getSerialNumber()) + ")");
				text.setPosition(j * 50.0f + 30, i * 70.0f + 50);
				window->draw(text);
				string num;
				if (cells[i][j].unit->getNumber() > 0)
					num = "x" + to_string(cells[i][j].unit->getNumber());
				else
					num = "";
				text.setString(num);
				text.setPosition(j * 50.0f + 25, i * 70.0f + 10);
				window->draw(text);

			}
			if (cells[i][j].netral->sprite != "")
			{
				sprite = f->getTexture(cells[i][j].netral)->sprite;
				sprite.setPosition(j * 50.0f, i * 70 + 10.0f);
				window->draw(sprite);
			}


			if (Point(i, j) == chosenUnit[0])
			{
				sf::Vertex line[] = { sf::Vertex(sf::Vector2f(j * 50.0f, i * 70.0f)), sf::Vertex(sf::Vector2f(j * 50.0f + 50, i * 70.0f)) };	line->color = sf::Color::Blue;
				window->draw(line, 2, sf::Lines);
				line[0] = sf::Vertex(sf::Vector2f(j * 50.0f, i * 70.0f));  line[1] = sf::Vertex(sf::Vector2f(j * 50.0f, i * 70.0f + 70)); line->color = sf::Color::Blue;
				window->draw(line, 2, sf::Lines);
				line[0] = sf::Vertex(sf::Vector2f(j * 50.0f, i * 70.0f + 70));  line[1] = sf::Vertex(sf::Vector2f(j * 50.0f + 50, i * 70.0f + 70)); line->color = sf::Color::Blue;
				window->draw(line, 2, sf::Lines);
				line[0] = sf::Vertex(sf::Vector2f(j * 50.0f + 50, i * 70.0f));  line[1] = sf::Vertex(sf::Vector2f(j * 50.0f + 50, i * 70.0f + 70)); line->color = sf::Color::Blue;
				window->draw(line, 2, sf::Lines);
			}

			if (Point(i, j) == chosenUnit[1])
			{
				sf::Vertex line[] = { sf::Vertex(sf::Vector2f(j * 50.0f, i * 70.0f)), sf::Vertex(sf::Vector2f(j * 50.0f + 50, i * 70.0f)) };	line->color = sf::Color::Red;
				window->draw(line, 2, sf::Lines);
				line[0] = sf::Vertex(sf::Vector2f(j * 50.0f, i * 70.0f));  line[1] = sf::Vertex(sf::Vector2f(j * 50.0f, i * 70.0f + 70)); line->color = sf::Color::Red;
				window->draw(line, 2, sf::Lines);
				line[0] = sf::Vertex(sf::Vector2f(j * 50.0f, i * 70.0f + 70));  line[1] = sf::Vertex(sf::Vector2f(j * 50.0f + 50, i * 70.0f + 70)); line->color = sf::Color::Red;
				window->draw(line, 2, sf::Lines);
				line[0] = sf::Vertex(sf::Vector2f(j * 50.0f + 50, i * 70.0f));  line[1] = sf::Vertex(sf::Vector2f(j * 50.0f + 50, i * 70.0f + 70)); line->color = sf::Color::Red;
				window->draw(line, 2, sf::Lines);
			}

		}
	}
	
	tileSet.loadFromFile("FireBase.png");
	sprite = sf::Sprite(tileSet);
	sprite.setPosition(900, 560);
	sprite.setScale(0.36f, 0.56f);
	window->draw(sprite);
	tileSet.loadFromFile("WaterBase.png");
	sprite = sf::Sprite(tileSet);
	sprite.setPosition(0, 0);
	sprite.setScale(0.22f, 0.4f);
	window->draw(sprite);

	text.setString("H: " + to_string(base.water->getHealth()));
	text.setPosition(60, 0);
	window->draw(text);
	text.setString("H: " + to_string(base.fire->getHealth()));
	text.setPosition(960, 560);
	window->draw(text);
	text.setString("G: " + to_string(base.water->getGold()));
	text.setPosition(0, 0);
	window->draw(text);
	text.setString("G: " + to_string(base.fire->getGold()));
	text.setPosition(900, 560);
	window->draw(text);
	
	sprite = (new WaterBerserks(10))->getSprite(0);
	sprite.setPosition(0, 700);
	window->draw(sprite);
	sprite = (new FireBerserks(10))->getSprite(0);
	sprite.setPosition(949, 700);
	window->draw(sprite);
	sprite = (new WaterCuirassiers(10))->getSprite(0);
	sprite.setPosition(50, 700);
	window->draw(sprite);
	sprite = (new FireCuirassiers(10))->getSprite(0);
	sprite.setPosition(900, 700);
	window->draw(sprite);
	sprite = (new WaterLongShooters(10))->getSprite(0);
	sprite.setPosition(110, 710);
	window->draw(sprite);
	sprite = (new FireLongShooters(10))->getSprite(0);
	sprite.setPosition(860, 710);
	window->draw(sprite);
	sprite = (new WaterSpearmen(10))->getSprite(0);
	sprite.setPosition(150, 710);
	window->draw(sprite);
	sprite = (new FireSpearmen(10))->getSprite(0);
	sprite.setPosition(800, 710);
	window->draw(sprite);

	
}
/*
void Field:: print() const
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width * 11; j++)
			cout << "-";
		cout << endl;
		cout << "|";

		for (int j = 0; j < width; j++)
		{
			if (!cells[i][j].unit->getTeam())
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 1) | 2));
			else
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 1) | 4));
			cout.width(2);
			if (cells[i][j].unit->getClass() != "  ")
				cout << "(" << cells[i][j].unit->getSerialNumber() << ")" << cells[i][j].unit->getClass()[0] << cells[i][j].unit->getSubclass()[0] << cells[i][j].unit->getSnum();
			else
				cout << "        ";
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 1) | 7));
			cout << " | ";
		}
		cout << endl;
	}
	for (int j = 0; j < width * 11; j++)
		cout << "-";
	cout << endl;
}*/
bool Field::check_point(int x, int y) const
{
	return(x >= 0 && y < width && y >= 0 && x < height);
}
Unit * Field::getUnit(int x, int y) const
{
	if (!check_point(y, x))
	{
		return nullptr;
	}
	return (cells[y][x].unit);
}
Base * Field::getBuilding(int x, int y)
{
	if ((x == 0 || x == 1) && (y == 0 || y == 1))
		return base.water;
	if ((x == width - 1 || x == width - 2) && ((x == height - 1 || x == height - 2)))
		return base.fire;
	return nullptr;
}

bool Field::addUnit(Point p, Unit * unit)
{
	if (!check_point(p.y, p.x))
	{
		return false;
	}

	if (!(cells[p.y][p.x].unit->isEmpty()))
	{
		return false;
	}

	cells[p.y][p.x].unit = unit;
	return true;
}
bool Field::moveUnit(int x1, int y1, int x2, int y2)
{
	if (!check_point(y1, x1) || !check_point(y2, x2))
	{
		return false;
	}
	if (!cells[y2][x2].land->isInteract(cells[y1][x1].unit))
	{
		return false;
	}
	if (!(cells[y2][x2].unit->isEmpty()))
	{
		return false;
	}
	if (cells[y1][x1].unit->isEmpty())
	{
		cells[y2][x2].unit = new EmptyUnit();
		return false;
	}
	cells[y2][x2].unit = cells[y1][x1].unit;
	cells[y1][x1].unit = new EmptyUnit();
	adapter->interact_Unit(cells[y2][x2].unit, cells[y2][x2].land->sprite);
	cells[y2][x2].land->interact(cells[y2][x2].unit);
	adapter->interact_Unit(cells[y2][x2].unit, cells[y2][x2].netral->sprite);
	*cells[y2][x2].netral >> (cells[y2][x2].unit);
	cells[y2][x2].netral = new EmptyObject();
	chosenUnit[cells[y2][x2].unit->getTeam()] = Point(y2,x2);
	return true;
}
WaterBase * Field::getWater()
{
	return base.water;
}
FireBase * Field::getFire()
{
	return base.fire;
}
Adapter * Field::getAdapter()
{
	return adapter;
}

bool Field::addNetral(Point p, Netral * n)
{
	if (!check_point(p.y, p.x))
	{
		return false;
	}
	cells[p.y][p.x].netral = n;
	return true;
}
bool Field::addLand(Point p, Land * l)
{
	if (!check_point(p.y, p.x))
	{
		return false;
	}
	cells[p.y][p.x].land = l;
	return true;
}