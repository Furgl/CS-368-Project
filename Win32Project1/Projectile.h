#pragma once

#include "SFML\Graphics.hpp"

class Projectile {

private:

	sf::RenderWindow & window;
	sf::Texture* texture;
	sf::Sprite sprite;
	sf::Vector2f destination;
	static const float SPEED;

public:

	bool reachedDestination;

	Projectile(sf::RenderWindow & window, int type, sf::Vector2f pos, sf::Vector2f destination, float rotation);
	void draw();

};
