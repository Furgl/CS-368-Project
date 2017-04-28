#pragma once

#include "SFML\Graphics.hpp"
#include "Tower.h"

class Tile {

private:

	sf::RenderWindow& window;
	sf::Sprite sprite;

public:

	sf::Vector2f pos;
	Tower* tower;
	// size of all (square) tiles
	const static int SIZE = 50;

	Tile(sf::RenderWindow& window, sf::Texture* texture, sf::Vector2f drawingPos);

	void draw();

};
