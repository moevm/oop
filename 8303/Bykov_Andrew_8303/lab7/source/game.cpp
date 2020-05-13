#include "GameFacade.h"

int main()
{
	Music music;
	music.openFromFile("music.ogg");
	GameFacade gameFacade;
	while (gameFacade.play())
	{
		if (Keyboard::isKeyPressed(Keyboard::Left))
			gameFacade.move();
		if (Keyboard::isKeyPressed(Keyboard::Right))
			gameFacade.move();
		if (Keyboard::isKeyPressed(Keyboard::Up))
			gameFacade.move();
		if (Keyboard::isKeyPressed(Keyboard::Down))
			gameFacade.move();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			gameFacade.click();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
			gameFacade.attack();
		if (Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::C))
			gameFacade.save();
		if (Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::V))
			gameFacade.load();
		if (Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::N))
			gameFacade.restart();
		if (Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::S))
			gameFacade.switchGameMod();
	}
	
	return 0;
}