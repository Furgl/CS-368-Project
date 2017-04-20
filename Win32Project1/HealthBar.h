#pragma once

#include <SFML/Graphics.hpp>

class HealthBar {

protected:

	sf::RenderWindow & window;

private:
	sf::RectangleShape rectangle;

public:

	HealthBar(sf::RenderWindow & window, int xPos, int yPos);

	// Draw the button
	virtual void draw();

	void HealthBar::update(double currentHealth, double maxHealth);

	void setPos(int x, int y);

};