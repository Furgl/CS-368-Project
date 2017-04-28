#include "ButtonTower.h"
#include "Tower.h"
#include <iomanip> 
#include <sstream> 

ButtonTower* ButtonTower::selected = nullptr;

ButtonTower::ButtonTower(sf::RenderWindow & window, Tower* tower) : Button(window), tower(tower) {
	rectangle.setSize(sf::Vector2f(64, 64));
	rectangle.setPosition(tower->pos);

	outlineTexture.loadFromFile("textures/tower_outline.png");
	outlineSprite.setTexture(outlineTexture);
	outlineSprite.setPosition(tower->pos);

	// load font
	font.loadFromFile("fonts/airstrike.ttf");

	costTxt.setFont(font);
	costTxt.setCharacterSize(20);
	costTxt.setFillColor(sf::Color::White);
	costTxt.setOutlineThickness(1);
	costTxt.setOutlineColor(sf::Color::Black);
	costTxt.setString("$" + std::to_string(tower->cost));
	costTxt.setPosition(sf::Vector2f(tower->pos.x + 32 - costTxt.getLocalBounds().width / 2, tower->pos.y + 45 - costTxt.getLocalBounds().height / 2));

	towerNameTxt.setStyle(sf::Text::Underlined);
	towerNameTxt.setOutlineThickness(1);
	towerNameTxt.setOutlineColor(sf::Color::Black);
	towerNameTxt.setFont(font);
	towerNameTxt.setCharacterSize(20);
	towerNameTxt.setFillColor(sf::Color::White);
	towerNameTxt.setPosition(sf::Vector2f(605, 260));

	towerTxt.setOutlineThickness(1);
	towerTxt.setOutlineColor(sf::Color::Black);
	towerTxt.setFont(font);
	towerTxt.setCharacterSize(20);
	towerTxt.setFillColor(sf::Color::White);
	towerTxt.setPosition(sf::Vector2f(605, 300));
}

void ButtonTower::draw() {
	tower->draw();
	window.draw(costTxt);

	if (ButtonTower::selected == this) {
		std::stringstream stream;
		stream << std::fixed << std::setprecision(0) << " Damage: " << tower->damage << "\n\n Range: " << tower->range <<
			"\n\n Attack Speed: " << tower->attackSpeed;
		towerTxt.setString(stream.str());
		towerNameTxt.setString(tower->name);
		window.draw(towerNameTxt);
		window.draw(towerTxt);
		window.draw(outlineSprite);
	}
	else if (Tower::selected != nullptr) {
		std::stringstream stream;
		stream << std::fixed << std::setprecision(0) << " Damage: " << Tower::selected->damage << "\n\n Range: " << Tower::selected->range <<
			"\n\n Attack Speed: " << Tower::selected->attackSpeed;
		towerTxt.setString(stream.str());
		towerNameTxt.setString(Tower::selected->name);
		window.draw(towerNameTxt);
		window.draw(towerTxt);
	}
}

void ButtonTower::onClick() {
	if (ButtonTower::selected == this)
		ButtonTower::selected = nullptr;
	else
		ButtonTower::selected = this;
}
