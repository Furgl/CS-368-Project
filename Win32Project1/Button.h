#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>

class Button {

protected:
	sf::RenderWindow& window;
	sf::Text text;
	sf::RectangleShape rectangle;

public:
	Button(sf::RenderWindow & window, std::string text, sf::Font & font, int x, int y, int textSize, int outlineSize);

	// Is the mouse currently above the button
	virtual bool isMouseOver(int x, int y);

	// Draw the button
	virtual void draw();

	// Called when isMouseOver is true and the mouse is clicked
	virtual int onClick();

};

#endif
