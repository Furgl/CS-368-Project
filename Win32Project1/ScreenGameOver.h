#pragma once

#include "Screen.h"
#include "SFML\Graphics.hpp"
#include "Stage.h"

class ScreenGameOver : public Screen {

private:

	sf::RectangleShape rectangle;
	sf::RectangleShape background;
	sf::Text winTxt;
	sf::Text loseTxt;
	bool win;
	sf::Texture screenshotTexture;
	sf::Sprite screenshotSprite;

public:

	ScreenGameOver(sf::RenderWindow & window);
	void Screen::draw() override;
	void setup(bool win);

};