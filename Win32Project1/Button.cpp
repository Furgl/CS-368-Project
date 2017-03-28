#include "Button.h"

Button::Button(sf::RenderWindow& window, std::string text, sf::Font& font,
	int x, int y, int textSize, int outlineSize)
: window(window), text(text, font), rectangle() {
	this->text.setCharacterSize(textSize);
	this->text.setPosition(x, y);
	this->text.setFillColor(sf::Color(20, 20, 30));

	// button background
	rectangle.setSize(sf::Vector2f(this->text.getLocalBounds().width + outlineSize * 2,
		this->text.getLocalBounds().height + outlineSize * 2));
	rectangle.setPosition(this->text.getGlobalBounds().left - outlineSize,
		this->text.getGlobalBounds().top - outlineSize);
	rectangle.setFillColor(sf::Color(166, 166, 190));
	rectangle.setOutlineThickness(outlineSize);
	rectangle.setOutlineColor(sf::Color(20, 20, 40));
}

bool Button::isMouseOver(int x, int y) {
	bool mouseOver = rectangle.getGlobalBounds().contains(x, y);
	if (mouseOver == true) 
		text.setFillColor(sf::Color(0, 100, 250));
	else 
		text.setFillColor(sf::Color(20, 20, 30));

	return mouseOver;
}

void Button::draw() {
	window.draw(rectangle);
	window.draw(text);
}

void Button::onClick() {}
