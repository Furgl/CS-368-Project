#pragma once
#include "SFML\Graphics.hpp"
class cScreen
{
public:
	virtual int Run(sf::RenderWindow &window) = 0;
};

