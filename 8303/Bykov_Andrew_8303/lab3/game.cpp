#include "GameFacade.h"

int main()
{
	GameFacade game;
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
	}
	
	return 0;
}