#include "HealthBar.h"


HealthBar::HealthBar(sf::RenderWindow &window, int xPos, int yPos) 
			:  window(window) {
	rectangle.setSize(sf::Vector2f(25, 5));
	rectangle.setFillColor(sf::Color::Green);
	rectangle.setOutlineColor(sf::Color::Black);
	rectangle.setOutlineThickness(2);
	setPos(xPos, yPos);
}

void HealthBar::draw() {
	window.draw(rectangle);
}

//updates the position to move with sprite
void HealthBar::setPos(int x, int y) {
	rectangle.setPosition(x - 12, y - 20);
}

//updates the health bar if hit
void HealthBar::update(double currentHealth, double maxHealth) {
	double percentage = currentHealth / maxHealth;
	rectangle.setSize(sf::Vector2f(25.0 * percentage, rectangle.getSize().y));
}