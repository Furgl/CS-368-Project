#pragma once

#include <SFML/Graphics.hpp>

class Button {

protected:

	sf::RenderWindow & window;
	sf::Text text;
	sf::RectangleShape rectangle;
	void (*clickFunc)(sf::RenderWindow & window);

public:

	Button(sf::RenderWindow & window, std::string text, sf::Font & font, int x, int y, int textSize, int outlineSize);

	Button(sf::RenderWindow & window, std::string text, sf::Font & font, int x, int y, int textSize, int outlineSize, 
		void (*onClick)(sf::RenderWindow & window));

	// Is the mouse currently above the button
	virtual bool isMouseOver(int x, int y);

	// Draw the button
	virtual void draw();

	// Called when isMouseOver is true and the mouse is clicked
	virtual void onClick();

};