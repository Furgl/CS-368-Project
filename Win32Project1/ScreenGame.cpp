#include "ScreenGame.h"
#include "Screen.h"
#include "SFML\Graphics.hpp"
#include "Button.h"
#include "Tile.h"
#include <sstream>
#include "main.h"
#include "Stage1.h"

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

	// create texts
	moneyTxt.setFont(font);
	moneyTxt.setCharacterSize(30);
	moneyTxt.setFillColor(sf::Color::White);
	moneyTxt.setPosition(sf::Vector2f(40, 10));

	livesTxt.setFont(font);
	livesTxt.setCharacterSize(30);
	livesTxt.setFillColor(sf::Color::White);
	livesTxt.setPosition(sf::Vector2f(50, 50));

	currentWaveTxt.setFont(font);
	currentWaveTxt.setCharacterSize(30);
	currentWaveTxt.setFillColor(sf::Color::White);
	currentWaveTxt.setPosition(sf::Vector2f(350, 10));

	timeToNextWaveTxt.setFont(font);
	timeToNextWaveTxt.setCharacterSize(30);
	timeToNextWaveTxt.setFillColor(sf::Color::White);
	timeToNextWaveTxt.setPosition(sf::Vector2f(330, 50));

	// create Save & Quit button
	buttons.push_back(new Button(window, "Save & Quit", font, 609, 550, 28, 3,
		[](sf::RenderWindow & window) {main::currentScreen = 0; }));

	// set current stage
	currentStage = new Stage1(window);
}

// temporary function - will be removed when we have towers
void ScreenGame::spacebar() {
	if (!currentStage->aliveEnemies.empty())
		currentStage->aliveEnemies[0]->attack(1);
}

void ScreenGame::draw() {

	// game over!
	if (currentStage->lives <= 0) {
		// do stuff
	}
	// all enemies have been spawned and defeated
	else if (currentStage->nextEnemy >= currentStage->waves.size() && currentStage->aliveEnemies.empty()) {
		// do stuff
	}

	// update texts
	moneyTxt.setString("Money: " + std::to_string(currentStage->money));
	livesTxt.setString("Lives: " + std::to_string(currentStage->lives));
	currentWaveTxt.setString("Wave: " + std::to_string(currentStage->getCurrentWave()) + " / " + std::to_string(currentStage->numWaves - 1));
	int timeToNextWave = currentStage->getTimeToNextWave();
	timeToNextWaveTxt.setString("Next Wave: " + (timeToNextWave == 0 ? "-" : std::to_string(timeToNextWave)));

	currentStage->draw();
	window.draw(topBar);
	window.draw(sideBar);
	window.draw(moneyTxt);
	window.draw(livesTxt);
	window.draw(currentWaveTxt);
	window.draw(timeToNextWaveTxt);
}
