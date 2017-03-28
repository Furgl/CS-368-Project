#include "ButtonPlay.h"

ButtonPlay::ButtonPlay(sf::RenderWindow& window, sf::Font& font, int x, int y)
	: Button(window, "Play", font, x, y, 50, 5) {
}

void ButtonPlay::onClick() {
	// TODO start game
}
