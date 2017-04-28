#include "ScreenGameOver.h"
#include "ScreenGame.h"
#include "Screen.h"
#include "SFML\Graphics.hpp"
#include "Button.h"
#include "Tile.h"
#include <sstream>
#include "main.h"
#include "Stage1.h"

ScreenGameOver::ScreenGameOver(sf::RenderWindow& window)
	: Screen(window) {

	// create background
	background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	background.setFillColor(sf::Color(100, 100, 100, 150));

	// create rectangle screen
	rectangle.setSize(sf::Vector2f(450, 250));
	rectangle.setOutlineColor(sf::Color::Cyan);
	rectangle.setOutlineThickness(3);
	rectangle.setFillColor(sf::Color::Blue);
	rectangle.setPosition(window.getSize().x/2-rectangle.getSize().x/2, window.getSize().y / 2 - rectangle.getSize().y / 2);

	// load font
	font.loadFromFile("fonts/airstrike.ttf");

	// create texts
	winTxt.setString("You Won!");
	winTxt.setFont(font);
	winTxt.setCharacterSize(70);
	winTxt.setStyle(sf::Text::Bold | sf::Text::Underlined);
	winTxt.setPosition(sf::Vector2f(window.getSize().x / 2 - winTxt.getLocalBounds().width / 2, 200));
	winTxt.setOutlineThickness(3);
	winTxt.setOutlineColor(sf::Color::Black);
	winTxt.setFillColor(sf::Color::Green);

	loseTxt.setString("You lost!");
	loseTxt.setFont(font);
	loseTxt.setCharacterSize(70);
	loseTxt.setStyle(sf::Text::Bold | sf::Text::Underlined);
	loseTxt.setPosition(sf::Vector2f(window.getSize().x / 2 - loseTxt.getLocalBounds().width / 2, 200));
	loseTxt.setOutlineThickness(3);
	loseTxt.setOutlineColor(sf::Color::Black);
	loseTxt.setFillColor(sf::Color::Red);

	// create screenshot texture for background screenshot
	screenshotTexture.create(window.getSize().x, window.getSize().y);

	// create vector of current buttons
	buttons.push_back(new Button(window, "Quit", font, 470, 342, 50, 5,
		[](sf::RenderWindow & window) {
		main::currentScreen = 0; 
		((ScreenGame*)main::screens[1])->startStage(1);
	}));
	buttons.push_back(new Button(window, "Retry", font, 205, 342, 50, 5,
		[](sf::RenderWindow & window) {
		main::currentScreen = 1;
		((ScreenGame*)main::screens[main::currentScreen])->startStage(1);
	}));
}

// set win field and take screenshot of game to put in background
void ScreenGameOver::setup(bool win) {
	this->win = win;
	screenshotTexture.update(window);
	screenshotSprite.setTexture(screenshotTexture);
}

void ScreenGameOver::draw() {
	window.draw(screenshotSprite);
	window.draw(background);
	window.draw(rectangle);
	if (win)
		window.draw(winTxt);
	else
		window.draw(loseTxt);
}
