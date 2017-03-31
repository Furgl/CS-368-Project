#include "configScreen.h"
#include "cScreen.h"
#include "SFML\Graphics.hpp"
#include "Button.h"
#include "ButtonExit.h"
#include "ButtonPlay.h"


int configScreen::Run(sf::RenderWindow &window)
{
	sf::RectangleShape rect;

	rect.setFillColor(sf::Color::Blue);
	rect.setSize({ 10.f,10.f });
	
	while (true)
	{
		window.clear(sf::Color::Black);
		window.draw(rect);
		window.display();
	}
	return -1;
}
