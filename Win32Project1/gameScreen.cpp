#include "gameScreen.h"
#include "cScreen.h"
#include "SFML\Graphics.hpp"
#include "Button.h"
#include "ButtonExit.h"
#include "ButtonPlay.h"
#include <sstream>

int gameScreen::Run(sf::RenderWindow &window)
{
	std::vector<Button*> buttons;
	int currMoney;
	int lives;

	//create side bar to place the towers later on
	sf::RectangleShape towerBar;
	towerBar.setSize(sf::Vector2f(100, window.getSize().y));
	towerBar.setOutlineColor(sf::Color::Cyan);
	towerBar.setOutlineThickness(3);
	towerBar.setFillColor(sf::Color::Blue);
	towerBar.setPosition(700, 0);


	// load font
	sf::Font font;
	if (!font.loadFromFile("fonts/airstrike.ttf"))
		window.close(); // error



	//Create money & lives text
	sf::Text moneyTxt;
	moneyTxt.setFont(font);
	moneyTxt.setString("Money: ");
	moneyTxt.setCharacterSize(15);
	moneyTxt.setFillColor(sf::Color::White);
	moneyTxt.setPosition(sf::Vector2f(1,2));

	sf::Text livesTxt;
	livesTxt.setFont(font);
	livesTxt.setString("Lives: ");
	livesTxt.setCharacterSize(15);
	livesTxt.setFillColor(sf::Color::White);
	livesTxt.setPosition(sf::Vector2f(1, 19));

	while (true)
	{
		window.clear(sf::Color::Black);
		
		sf::Event event;
		while (window.pollEvent(event)) {

			// close window when requested
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		// end current frame
		window.draw(moneyTxt);
		window.draw(livesTxt);
		window.draw(towerBar);
		window.display();
	}

	return -1;
}
