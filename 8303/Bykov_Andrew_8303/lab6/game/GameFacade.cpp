#include "GameFacade.h"
#include "Snapshot.h"


const int HEIGHT = 900;
const int WIDTH = 1000;
const int CELL_W = 50;
const int CELL_H = 70;
int Field_W = 20;
int Field_H = 10;
Game<Rule1> * Game<Rule1>::game = nullptr;
Game<Rule2> * Game<Rule2>::game = nullptr;

GameFacade::GameFacade()
{
	tileSet.loadFromFile("Grass.png");
	tile.setTexture(tileSet);
	tile.setScale(0.53f, 0.65f);
	window = new RenderWindow(VideoMode(WIDTH, HEIGHT), "Game!");
	auto * game = Game<Rule1>::getInstance();
	game->startGame();
	field = game->field;
	adapter = field->getAdapter();
	adapter->createField(field);
	base[0] = field->getWater();
	adapter->createBase(base[0]);
	base[1] = field->getFire();
	adapter->createBase(base[1]);
}

bool GameFacade::play()
{
	base[0] = field->getWater();
	base[1] = field->getFire();
	float time = float(clock.getElapsedTime().asMicroseconds());
	clock.restart();

	time = time / 500;

	if (time > 20) time = 20;

	if (!(Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::Right)
		|| Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Down)
		|| Mouse::isButtonPressed(sf::Mouse::Button::Right) || Keyboard::isKeyPressed(Keyboard::Tab) || Mouse::isButtonPressed(sf::Mouse::Button::Left) 
		|| Keyboard::isKeyPressed(Keyboard::LControl) || Keyboard::isKeyPressed(Keyboard::C)))
		clicked = true;

	window->draw(tile);
	field->paint(window, time);
	window->display();
	
	Event event;
	while (window->pollEvent(event))
	{
		if (event.type == Event::Closed)
			window->close();
	}
	return(window->isOpen());
}
void GameFacade::move()
{
	if (!gameInProcess) return;
	if (clicked)
	{
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			adapter->move_Player("Left");
			if (mod)
				gameInProcess = Game<Rule1>::getInstance()->doCommand(new MoveCommand(MoveCommand::dirs::Left));
			else
				gameInProcess = Game<Rule2>::getInstance()->doCommand(new MoveCommand( MoveCommand::dirs::Left));
			clicked = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			adapter->move_Player("Right");
			if (mod)
				gameInProcess = Game<Rule1>::getInstance()->doCommand(new MoveCommand(MoveCommand::dirs::Right));
			else
				gameInProcess = Game<Rule2>::getInstance()->doCommand(new MoveCommand(MoveCommand::dirs::Right));
			clicked = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			adapter->move_Player("Up");
			if (mod)
				gameInProcess = Game<Rule1>::getInstance()->doCommand(new MoveCommand(MoveCommand::dirs::Up));
			else
				gameInProcess = Game<Rule2>::getInstance()->doCommand(new MoveCommand(MoveCommand::dirs::Up));
			clicked = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			adapter->move_Player("Down");
			if (mod)
				gameInProcess = Game<Rule1>::getInstance()->doCommand(new MoveCommand( MoveCommand::dirs::Down));
			else
				gameInProcess = Game<Rule2>::getInstance()->doCommand(new MoveCommand(MoveCommand::dirs::Down));
			clicked = false;
		}
	}
}
void GameFacade::click()
{
	if (!gameInProcess) return;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && clicked)
	{
		sf::Vector2i localPosition = Mouse::getPosition(*window);
		if (field->check_point(localPosition.y / CELL_H, localPosition.x / CELL_W))
		{
			if (localPosition.y > 0 && localPosition.y < 140 && localPosition.x > 0 && localPosition.x < 100)
			{
				base[0]->printInfo(); clicked = false;
				return;
			}
			if (localPosition.y > 560 && localPosition.y < 700 && localPosition.x > 900 && localPosition.x < 1000)
			{
				base[1]->printInfo(); clicked = false;
				return;
			}
			Unit * unit = field->getUnit(localPosition.x / CELL_W, localPosition.y / CELL_H);
			if (unit->getClass() != "nan")
			{
				if (unit->getBase() == base[0]) flip = 0;
				else flip = 1;
				field->chosenUnit[flip] = Point(localPosition.y / CELL_H, localPosition.x / CELL_W);
				base[flip]->currentSquad = unit->getSerialNumber();
			}
		}
		else
		{

			if (localPosition.y > 700 && localPosition.y < 770 && localPosition.x > 0 && localPosition.x < 45)
			{
				adapter->create_Player("Berserks");
				base[0]->order(new CreateCommand("IB", "50"));				
			}
			if (localPosition.y > 700 && localPosition.y < 770 && localPosition.x > 950 && localPosition.x < 1000)
			{
				adapter->create_Player("Berserks");
				base[1]->order(new CreateCommand("IB", "50"));				
			}
			if (localPosition.y > 700 && localPosition.y < 770 && localPosition.x > 46 && localPosition.x < 97)
			{
				adapter->create_Player("Cuirassiers");
				base[0]->order(new CreateCommand("CC", "2"));
			}
			if (localPosition.y > 700 && localPosition.y < 770 && localPosition.x > 900 && localPosition.x < 950)
			{
				adapter->create_Player("Cuirassiers");
				base[1]->order(new CreateCommand("CC", "2"));
			}
			if (localPosition.y > 700 && localPosition.y < 770 && localPosition.x > 100 && localPosition.x < 150)
			{
				adapter->create_Player("LongShooters");
				base[0]->order(new CreateCommand("AL", "2"));
			}
			if (localPosition.y > 700 && localPosition.y < 770 && localPosition.x > 850 && localPosition.x < 900)
			{
				adapter->create_Player("LongShooters");
				base[1]->order(new CreateCommand("AL", "2"));				
			}
			if (localPosition.y > 700 && localPosition.y < 770 && localPosition.x > 150 && localPosition.x < 200)
			{
				adapter->create_Player("Spearmen");
				base[0]->order(new CreateCommand("IS", "2"));				
			}
			if (localPosition.y > 700 && localPosition.y < 770 && localPosition.x > 800 && localPosition.x < 850)
			{
				adapter->create_Player("Spearmen");
				base[1]->order(new CreateCommand("IS", "2"));				
			}
				
		}
		clicked = false;
	}
}
void GameFacade::attack() 
{
	if (!gameInProcess) return;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && clicked)
	{
		sf::Vector2i localPosition = Mouse::getPosition(*window);
		if (field->check_point(localPosition.y / CELL_H, localPosition.x / CELL_W))
		{
			adapter->attack_Player(to_string(localPosition.x / CELL_W) + "," + to_string(localPosition.y / CELL_H));
			Unit * unit = field->getUnit(localPosition.x / CELL_W, localPosition.y / CELL_H);
			if (mod)
				gameInProcess = Game<Rule1>::getInstance()->doCommand(new AttackCommand(to_string(localPosition.x / CELL_W), to_string(localPosition.y / CELL_H)));
			else
				gameInProcess = Game<Rule2>::getInstance()->doCommand(new AttackCommand(to_string(localPosition.x / CELL_W), to_string(localPosition.y / CELL_H)));
			
			
		}
		clicked = false;
	}
}
void GameFacade::save()
{
	if (Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::C) && clicked)
	{
		adapter->gameSaved();
		Snapshot * snap = new Snapshot(field, "save");
		clicked = false;
	}
}
void GameFacade::load()
{
	if (Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::V) && clicked)
	{
		adapter->gameLoad();
		Snapshot * snap = new Snapshot(field, "load");
		clicked = false;

	}
}

void GameFacade::fileON()
{
	adapter->fileWriteAble = true;
	adapter->switchLog("FILE_ON");
}
void GameFacade::fileOFF()
{
	adapter->fileWriteAble = false;
	adapter->switchLog("FILE_OFF");
}
void GameFacade::logOFF()
{
	adapter->writeAble = false;
	adapter->switchLog("LOGS_OFF");
}
void GameFacade::logON()
{
	adapter->writeAble = true;
	adapter->switchLog("LOGS_ON");
}
void GameFacade::restart()
{
	if (clicked)
	{
		gameInProcess = true;
		if (mod)
		{
			auto * game = Game<Rule1>::getInstance();
			game->startGame();
			field = game->field;
			adapter = field->getAdapter();
			base[0] = field->getWater();
			adapter->createBase(base[0]);
			base[1] = field->getFire();
			adapter->createBase(base[1]);
		}
		else
		{
			auto * game = Game<Rule2>::getInstance();
			game->startGame();
			field = game->field;
			adapter = field->getAdapter();
			base[0] = field->getWater();
			adapter->createBase(base[0]);
			base[1] = field->getFire();
			adapter->createBase(base[1]);
		}
		clicked = false;
	}
	
}
void  GameFacade::switchGameMod()
{
	if (clicked)
	{
		mod = !mod;
		restart();
		clicked = false;
	}
	
}
