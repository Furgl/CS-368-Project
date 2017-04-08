#pragma once

#include "Screen.h"
#include "SFML\Graphics.hpp"
#include "Stage.h"

class ScreenGame : public Screen {

private:

	sf::RectangleShape topBar;
	sf::RectangleShape sideBar;
	sf::Text moneyTxt;
	sf::Text livesTxt;
	int money = 1000;
	int lives = 50;
	std::vector<sf::RectangleShape> lines;
	Stage* currentStage;

public:

	ScreenGame(sf::RenderWindow & window);
	void Screen::run() override;

};