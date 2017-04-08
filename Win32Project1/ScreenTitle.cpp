#include "ScreenTitle.h"
#include "Screen.h"
#include "SFML\Graphics.hpp"
#include "Button.h"
#include "main.h"

ScreenTitle::ScreenTitle(sf::RenderWindow& window) 
	: Screen(window) {

	// load background texture
	backgroundTexture.loadFromFile("textures/title_background.jpg");
	backgroundTexture.setSmooth(true);
	background.setTexture(backgroundTexture);
	background.setTextureRect(sf::IntRect(25, 0, window.getSize().x, window.getSize().y));
	background.setScale(sf::Vector2f(1.25f, 1.25f));

	// load font
	font.loadFromFile("fonts/airstrike.ttf");

	// create title text
	title.setFont(font);
	title.setString("Tower Defense");
	title.setCharacterSize(70);
	title.setFillColor(sf::Color::Blue);
	title.setStyle(sf::Text::Bold | sf::Text::Underlined);
	title.setPosition(sf::Vector2f(window.getSize().x / 2 - title.getLocalBounds().width / 2, 150));
	title.setOutlineThickness(3);
	title.setOutlineColor(sf::Color(40, 100, 200));

	// create vector of current buttons
	buttons.push_back(new Button(window, "Exit", font, 480, 342, 50, 5, 
		[](sf::RenderWindow & window) {window.close();}));
	buttons.push_back(new Button(window, "Play", font, 190, 342, 50, 5,
		[](sf::RenderWindow & window) {main::currentScreen = 1;}));
}

void ScreenTitle::run() {
	sf::Uint8 fade = abs(cos(main::counter * (double) 0.0002) * 80) + 130;
	background.setColor(sf::Color(fade, fade, fade));

	// draw everything here
	window.draw(background);
	window.draw(title);
}