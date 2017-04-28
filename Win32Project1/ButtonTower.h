#pragma once
#include "Button.h"
#include "Tower.h"

class ButtonTower : public Button {

private:

	sf::Texture outlineTexture;
	sf::Sprite outlineSprite;
	sf::Font font;
	sf::Text costTxt;
	sf::Text towerTxt;
	sf::Text towerNameTxt;

public:

	Tower* tower;
	static ButtonTower* selected;

	ButtonTower(sf::RenderWindow & window, Tower* tower);
	void draw() override;
	void onClick() override;

};
