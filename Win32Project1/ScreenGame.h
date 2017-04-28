#pragma once

#include "Screen.h"
#include "SFML\Graphics.hpp"
#include "Stage.h"
#include "ButtonSell.h"

class ScreenGame : public Screen {

private:

	sf::RectangleShape topBar;
	sf::RectangleShape sideBar;
	sf::Text moneyTxt;
	sf::Text livesTxt;
	sf::Text currentWaveTxt;
	sf::Text timeToNextWaveTxt;
	sf::Text towersTxt;
	Stage* currentStage = nullptr;
	ButtonSell* sellButton;

public:

	ScreenGame(sf::RenderWindow & window);
	void startStage(int stage);
	void draw() override;
	void click(float x, float y) override;

};