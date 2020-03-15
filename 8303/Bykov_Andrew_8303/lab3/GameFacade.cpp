#include "GameFacade.h"

const int HEIGHT = 900;
const int WIDTH = 1000;
const int CELL_W = 50;
const int CELL_H = 70;
int Field_W = 20;
int Field_H = 10;

GameFacade::GameFacade()
{
	tileSet.loadFromFile("Grass.png");
	tile.setTexture(tileSet);
	tile.setScale(0.53f, 0.65f);
	window = new RenderWindow(VideoMode(WIDTH, HEIGHT), "Game!");
	field = new Field(20, 10);
	base[0] = field->getWater();
	base[1] = field->getFire();
}

bool GameFacade::play()
{
	float time = float(clock.getElapsedTime().asMicroseconds());
	clock.restart();

	time = time / 500;

	if (time > 20) time = 20;

	if (!(Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::Right)
		|| Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Down)
		|| Mouse::isButtonPressed(sf::Mouse::Button::Right) || Keyboard::isKeyPressed(Keyboard::Tab) || Mouse::isButtonPressed(sf::Mouse::Button::Left)))
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
	if (squad && clicked)
	{
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			base[flip]->order(new MoveCommand(base[flip], to_string(squad), MoveCommand::dirs::Left)); clicked = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			base[flip]->order(new MoveCommand(base[flip], to_string(squad), MoveCommand::dirs::Right)); clicked = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			base[flip]->order(new MoveCommand(base[flip], to_string(squad), MoveCommand::dirs::Up)); clicked = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			base[flip]->order(new MoveCommand(base[flip], to_string(squad), MoveCommand::dirs::Down)); clicked = false;
		}
	}
}
void GameFacade::click()
{
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
			if (unit->getTeam() == flip || unit->getClass() == "  ")
			{
				field->chosenUnit[flip] = Point(localPosition.y / CELL_H, localPosition.x / CELL_W);
				squad = unit->getSerialNumber();
			}
		}
		else
		{

			if (localPosition.y > 700 && localPosition.y < 770 && localPosition.x > 0 && localPosition.x < 45)
				base[0]->order(new CreateCommand(base[0], "IB", "50"));
			if (localPosition.y > 700 && localPosition.y < 770 && localPosition.x > 950 && localPosition.x < 1000)
				base[1]->order(new CreateCommand(base[1], "IB", "50"));
			if (localPosition.y > 700 && localPosition.y < 770 && localPosition.x > 46 && localPosition.x < 97)
				base[0]->order(new CreateCommand(base[0], "CC", "2"));
			if (localPosition.y > 700 && localPosition.y < 770 && localPosition.x > 900 && localPosition.x < 950)
				base[1]->order(new CreateCommand(base[1], "CC", "2"));
			if (localPosition.y > 700 && localPosition.y < 770 && localPosition.x > 100 && localPosition.x < 150)
				base[0]->order(new CreateCommand(base[0], "AL", "2"));
			if (localPosition.y > 700 && localPosition.y < 770 && localPosition.x > 850 && localPosition.x < 900)
				base[1]->order(new CreateCommand(base[1], "AL", "2"));
			if (localPosition.y > 700 && localPosition.y < 770 && localPosition.x > 150 && localPosition.x < 200)
				base[0]->order(new CreateCommand(base[0], "IS", "2"));
			if (localPosition.y > 700 && localPosition.y < 770 && localPosition.x > 800 && localPosition.x < 850)
				base[1]->order(new CreateCommand(base[1], "IS", "2"));
		}
		clicked = false;
	}
}
void GameFacade::attack() 
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && squad && clicked)
	{
		sf::Vector2i localPosition = Mouse::getPosition(*window);
		if (field->check_point(localPosition.y / CELL_H, localPosition.x / CELL_W))
		{
			Unit * unit = field->getUnit(localPosition.x / CELL_W, localPosition.y / CELL_H);
			if (unit->getTeam() != flip)
				base[flip]->order(new AttackCommand(base[flip], to_string(squad), to_string(localPosition.x / CELL_W), to_string(localPosition.y / CELL_H)));
		}
		clicked = false;
	}
}
void GameFacade::switchUsers() 
{
	if (Keyboard::isKeyPressed(Keyboard::Tab) && clicked)
	{
		field->chosenUnit[flip] = Point(-1, -1);
		if (flip) flip = 0;
		else flip = 1;
		clicked = false;
	}
}
