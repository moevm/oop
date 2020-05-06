#include "GameFacade.h"

int main()
{
	Music music;
	music.openFromFile("music.ogg");
	//music.play();
	GameFacade game;
	//game.fileON();
	while (game.play())
	{
		if (Keyboard::isKeyPressed(Keyboard::Left))
			game.move();
		if (Keyboard::isKeyPressed(Keyboard::Right))
			game.move();
		if (Keyboard::isKeyPressed(Keyboard::Up))
			game.move();
		if (Keyboard::isKeyPressed(Keyboard::Down))
			game.move();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			game.click();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
			game.attack();
		if (Keyboard::isKeyPressed(Keyboard::Tab))
			game.switchUsers();
		if (Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::C))
			game.save();
		if (Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::V))
			game.load();
	}
	
	return 0;
}