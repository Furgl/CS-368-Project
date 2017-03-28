#include "ButtonExit.h"

ButtonExit::ButtonExit(sf::RenderWindow& window, sf::Font& font, int x, int y) 
 : Button(window, "Exit", font, x, y, 50, 5) {
}

void ButtonExit::onClick() {
	window.close();
}
