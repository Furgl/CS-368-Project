#include "ScreenGame.h"
#include "Screen.h"
#include "SFML\Graphics.hpp"
#include "Button.h"
#include "main.h"
#include "Tile.h"
#include "Stage1.h"
#include <sstream>

ScreenGame::ScreenGame(sf::RenderWindow& window)
	: Screen(window) {

	// create top bar and side bar for money, lives, towers, etc.
	topBar.setSize(sf::Vector2f(window.getSize().x, 98.5f));
	topBar.setOutlineColor(sf::Color::Cyan);
	topBar.setOutlineThickness(3);
	topBar.setFillColor(sf::Color::Blue);
	topBar.setPosition(0, (float) -1.5);

	sideBar.setSize(sf::Vector2f(198.5f, window.getSize().y));
	sideBar.setOutlineColor(sf::Color::Cyan);
	sideBar.setOutlineThickness(3);
	sideBar.setFillColor(sf::Color::Blue);
	sideBar.setPosition((float) 601.5, 0);

	// load font
	font.loadFromFile("fonts/airstrike.ttf");

	// create money & lives text
	moneyTxt.setFont(font);
	moneyTxt.setCharacterSize(30);
	moneyTxt.setFillColor(sf::Color::White);
	moneyTxt.setPosition(sf::Vector2f(15, 10));

	livesTxt.setFont(font);
	livesTxt.setCharacterSize(30);
	livesTxt.setFillColor(sf::Color::White);
	livesTxt.setPosition(sf::Vector2f(15, 50));

	// create Save & Quit button
	buttons.push_back(new Button(window, "Save & Quit", font, 609, 550, 28, 3,
		[](sf::RenderWindow & window) {main::currentScreen = 0; }));

	// create game board lines
	float space = Tile::SIZE;
	for (int row = 0; row <= (float) 600 / space; ++row) {
		sf::RectangleShape line(sf::Vector2f(2, 500));
		line.setPosition(row*space, 100);
		lines.push_back(line);
	}
	for (int col = 0; col <= (float) 500 / space; ++col) {
		sf::RectangleShape line(sf::Vector2f(600, 2));
		line.setPosition(0, col*space + 98);
		lines.push_back(line);
	}

	// set current stage
	currentStage = new Stage1(window);
}

void ScreenGame::run() {

	// update money and lives
	moneyTxt.setString("Money: " + std::to_string(money));
	livesTxt.setString("Lives: " + std::to_string(lives));

	currentStage->draw();
	sf::Uint8 fade = abs(cos(main::counter * (double) 0.0004) * 80);
	for (sf::RectangleShape line : lines) {
		line.setFillColor(sf::Color(100, 150, 210, 20 + fade));
		window.draw(line);
	}
	window.draw(topBar);
	window.draw(sideBar);
	window.draw(moneyTxt);
	window.draw(livesTxt);
}
