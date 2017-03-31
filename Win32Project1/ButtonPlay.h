#ifndef BUTTON_PLAY_HPP
#define BUTTON_PLAY_HPP

#include "Button.h"
#include <SFML/Graphics.hpp>

class ButtonPlay : public Button {

private:

public:
	ButtonPlay(sf::RenderWindow & window, sf::Font & font, int x, int y);

	// Called when isMouseOver is true and the mouse is clicked
	int onClick() override;
};

#endif
