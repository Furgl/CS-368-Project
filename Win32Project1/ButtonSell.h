#pragma once

#include "Button.h"
#include "Stage.h"
#include <functional>

class ButtonSell : public Button {

public:

	Stage* stage;

	ButtonSell(sf::RenderWindow & window, std::string text, sf::Font & font, int x, int y, int textSize, int outlineSize, Stage* currentStage);

	void draw() override;
	void onClick() override;

};
