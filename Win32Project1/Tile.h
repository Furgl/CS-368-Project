#pragma once

#include "SFML\Graphics.hpp"

class Tile {

private:

	sf::RenderWindow& window;
	sf::Sprite sprite;
	// Tower tower;

public:

	// size of all (square) tiles
	const static int SIZE = 50;

	Tile(sf::RenderWindow& window, sf::Texture* texture, sf::Vector2f drawingPos);

	void draw();

};
