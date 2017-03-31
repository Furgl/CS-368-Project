#pragma once
#include "cScreen.h"
#include "SFML\Graphics.hpp"

class configScreen : public cScreen
{
public:
	virtual int Run(sf::RenderWindow &window);
};

