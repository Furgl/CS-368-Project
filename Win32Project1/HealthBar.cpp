#include "HealthBar.h"


HealthBar::HealthBar(sf::RenderWindow &window, int xPos, int yPos) 
			:  window(window),rectangle() {

	rectangle.setSize(sf::Vector2f(25, 5));
	rectangle.setFillColor(sf::Color::Green);
	rectangle.setOutlineColor(sf::Color::Black);
	rectangle.setOutlineThickness(2);
	rectangle.setPosition(xPos- 12, yPos- 20);

}

void HealthBar::draw() {
	window.draw(rectangle);
}

//updates teh position to move with sprite
void HealthBar::setPos(int x, int y) {
	rectangle.setPosition(x - 12, y - 20);
}

//updates the health bar if hit, may need to add another parameter for the amount of damage hit did
int HealthBar::hit(double damage, double health) {

	//if the damage will kill the enemy
	if (damage > health)
		return 1;

	//Otherwise update the health bar
	else {

		//expression to find how much health bar should change
		double percentLost = damage / health;
		double barChange = percentLost * rectangle.getSize().x;

		rectangle.setSize(sf::Vector2f(rectangle.getSize().x - barChange, rectangle.getSize().y));
		return 0;

	}

	//shouldn't ever get here
	return 0;
}