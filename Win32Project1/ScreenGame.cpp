#include "ScreenGame.h"
#include "ScreenGameOver.h"
#include "Screen.h"
#include "SFML\Graphics.hpp"
#include "ButtonTower.h"
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
	moneyTxt.setOutlineThickness(1);
	moneyTxt.setOutlineColor(sf::Color::Black);
	moneyTxt.setCharacterSize(30);
	moneyTxt.setFillColor(sf::Color::White);
	moneyTxt.setPosition(sf::Vector2f(40, 10));

	livesTxt.setFont(font);
	livesTxt.setOutlineThickness(1);
	livesTxt.setOutlineColor(sf::Color::Black);
	livesTxt.setCharacterSize(30);
	livesTxt.setFillColor(sf::Color::White);
	livesTxt.setPosition(sf::Vector2f(50, 50));

	currentWaveTxt.setFont(font);
	currentWaveTxt.setOutlineThickness(1);
	currentWaveTxt.setOutlineColor(sf::Color::Black);
	currentWaveTxt.setCharacterSize(30);
	currentWaveTxt.setFillColor(sf::Color::White);
	currentWaveTxt.setPosition(sf::Vector2f(350, 10));

	timeToNextWaveTxt.setFont(font);
	timeToNextWaveTxt.setOutlineThickness(1);
	timeToNextWaveTxt.setOutlineColor(sf::Color::Black);
	timeToNextWaveTxt.setCharacterSize(30);
	timeToNextWaveTxt.setFillColor(sf::Color::White);
	timeToNextWaveTxt.setPosition(sf::Vector2f(330, 50));

	towersTxt.setFont(font);
	towersTxt.setStyle(sf::Text::Underlined | sf::Text::Bold);
	towersTxt.setOutlineThickness(1);
	towersTxt.setOutlineColor(sf::Color::Black);
	towersTxt.setCharacterSize(40);
	towersTxt.setFillColor(sf::Color::White);
	towersTxt.setPosition(sf::Vector2f(610, 15));
	towersTxt.setString("Towers");

	// create sell tower button
	sellButton = new ButtonSell(window, "Sell $20", font, 615, 400, 35, 3, currentStage);
	buttons.push_back(sellButton);

	// create Save & Quit button
	buttons.push_back(new Button(window, "Save & Quit", font, 609, 550, 28, 3,
		[](sf::RenderWindow & window) {main::currentScreen = 0; }));

	// create tower buttons
	buttons.push_back(new ButtonTower(window, new Tower(window, sf::Vector2f(630, 100), 1, nullptr)));
	buttons.push_back(new ButtonTower(window, new Tower(window, sf::Vector2f(714, 100), 2, nullptr)));
	buttons.push_back(new ButtonTower(window, new Tower(window, sf::Vector2f(630, 184), 3, nullptr)));
	buttons.push_back(new ButtonTower(window, new Tower(window, sf::Vector2f(714, 184), 4, nullptr)));

	// set current stage
	startStage(1);
}

// start a stage
void ScreenGame::startStage(int stage) {
	// clear selected towers/buttons
	ButtonTower::selected = nullptr;
	Tower::selected = nullptr;

	if (stage == 1)
		currentStage = new Stage1(window);

	sellButton->stage = currentStage;
}

void ScreenGame::click(float x, float y) {
	// clicking on game board
	if (!topBar.getGlobalBounds().contains(x, y) && !sideBar.getGlobalBounds().contains(x, y)) {
		sf::Vector2f boardPos = Enemy::getBoardPos(sf::Vector2f(x, y));
		// make sure boardpos is valid
		if (currentStage->tiles.size() >= boardPos.x && currentStage->tiles[boardPos.x].size() >= boardPos.y) {
			// if a tower is already there, select it
			if (currentStage->tiles[boardPos.x][boardPos.y].tower != nullptr) {
				ButtonTower::selected = nullptr;
				if (Tower::selected == currentStage->tiles[boardPos.x][boardPos.y].tower)
					Tower::selected = nullptr;
				else
					Tower::selected = currentStage->tiles[boardPos.x][boardPos.y].tower;
			}
			// if tower can be placed there and player has enough money, place it there
			else if (ButtonTower::selected != nullptr && currentStage->map[boardPos.x][boardPos.y] == 0 &&
				currentStage->money >= ButtonTower::selected->tower->cost) {
				currentStage->tiles[boardPos.x][boardPos.y].tower =
					new Tower(window, currentStage->tiles[boardPos.x][boardPos.y].pos, ButtonTower::selected->tower->type, &currentStage->aliveEnemies);
				currentStage->money -= ButtonTower::selected->tower->cost;
				Tower::selected = nullptr;
			}
			else 
				Tower::selected = nullptr;
		}
	}
	else {
		Tower::selected = nullptr;

		bool clickedOnButton = false;
		for (Button* button : main::screens[main::currentScreen]->buttons)
			if (button->isMouseOver(x, y))
				clickedOnButton = true;
		if (!clickedOnButton)
			ButtonTower::selected = nullptr;
	}
}

void ScreenGame::draw() {
	currentStage->draw();

	// update texts
	moneyTxt.setString("Money: $" + std::to_string(currentStage->money));
	livesTxt.setString("Lives: " + std::to_string(currentStage->lives));
	currentWaveTxt.setString("Wave: " + std::to_string(currentStage->getCurrentWave()) + " / " + std::to_string(currentStage->numWaves - 1));
	int timeToNextWave = currentStage->getTimeToNextWave();
	timeToNextWaveTxt.setString("Next Wave: " + (timeToNextWave == 0 ? "-" : std::to_string(timeToNextWave)));

	window.draw(topBar);
	window.draw(sideBar);
	window.draw(moneyTxt);
	window.draw(livesTxt);
	window.draw(currentWaveTxt);
	window.draw(timeToNextWaveTxt);
	window.draw(towersTxt);

	// game over!
	if (currentStage->lives <= 0) {
		for (Button* button : main::screens[main::currentScreen]->buttons)
			button->draw();
		main::currentScreen = 2;
		((ScreenGameOver*)main::screens[main::currentScreen])->setup(false);
	}
	// all enemies have been spawned and defeated
	else if (currentStage->nextEnemy >= currentStage->waves.size() && currentStage->aliveEnemies.empty()) {
		for (Button* button : main::screens[main::currentScreen]->buttons)
			button->draw();
		main::currentScreen = 2;
		((ScreenGameOver*)main::screens[main::currentScreen])->setup(true);
	}
}
