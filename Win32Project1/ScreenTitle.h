#pragma once

#include "Screen.h"
#include "SFML\Graphics.hpp"

class ScreenTitle : public Screen {

private:

	sf::Sprite background;
	sf::Texture backgroundTexture;
	sf::Text title;

public:

	ScreenTitle(sf::RenderWindow & window);
	void Screen::draw() override;
	void spacebar() override {}

};