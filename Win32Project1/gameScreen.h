#pragma once
#include "cScreen.h"
#include "SFML\Graphics.hpp"

class gameScreen : public cScreen
{
public:
	virtual int Run(sf::RenderWindow &window);
};

