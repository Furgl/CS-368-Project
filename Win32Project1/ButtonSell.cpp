#include "ButtonSell.h"
#include "Tower.h"

ButtonSell::ButtonSell(sf::RenderWindow & window, std::string text, sf::Font & font, 
	int x, int y, int textSize, int outlineSize, Stage* currentStage)
	: Button(window, text, font, x, y, textSize, outlineSize) {
	stage = currentStage;
	rectangle.setFillColor(sf::Color::Red);
}

void ButtonSell::draw() {
	this->text.setFillColor(sf::Color::White);
	if (Tower::selected != nullptr) {
		window.draw(rectangle);
		text.setString("Sell $" + std::to_string(Tower::selected->cost));
		window.draw(text);
	}
}

void ButtonSell::onClick() {
	if (Tower::selected != nullptr) {
		for (int row = 0; row < stage->tiles.size(); ++row)
			for (int col = 0; col < stage->tiles[row].size(); ++col)
				if (stage->tiles[row][col].tower == Tower::selected && stage->tiles[row][col].tower != nullptr)
					stage->tiles[row][col].tower = nullptr;
		stage->money += Tower::selected->cost;
		Tower::selected = nullptr;
	}
}
