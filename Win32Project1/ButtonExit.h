#ifndef BUTTON_EXIT_HPP
#define BUTTON_EXIT_HPP

#include "Button.h"
#include <SFML/Graphics.hpp>

class ButtonExit: public Button {

private:

public:
	ButtonExit(sf::RenderWindow & window, sf::Font & font, int x, int y);

	// Called when isMouseOver is true and the mouse is clicked
	void onClick() override;
};

#endif
