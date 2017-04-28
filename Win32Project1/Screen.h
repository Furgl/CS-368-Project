#pragma once

#include "Button.h"
#include "SFML\Graphics.hpp"
#include <memory>

class Screen {

protected:
	sf::RenderWindow& window;
	sf::Font font;

public:

	std::vector<Button*> buttons;

	Screen(sf::RenderWindow & window) : window(window) {}
	virtual void draw() = 0;
	virtual void click(float x, float y) {}

};