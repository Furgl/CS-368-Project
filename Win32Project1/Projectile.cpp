#include "Projectile.h"

const float Projectile::SPEED = 3;

Projectile::Projectile(sf::RenderWindow & window, int type, sf::Vector2f pos, sf::Vector2f destination, float rotation)
	: window(window), destination(destination) {
	reachedDestination = false;

	texture = new sf::Texture;
	switch (type) {
	case 1:
		texture->loadFromFile("textures/projectile_1.png");
		break;
	case 2:
		texture->loadFromFile("textures/projectile_2.png");
		break;
	case 3:
		texture->loadFromFile("textures/projectile_3.png");
		break;
	case 4:
		texture->loadFromFile("textures/projectile_4.png");
		break;
	}

	sprite.setRotation(rotation);
	sprite.setTexture(*texture);
	sprite.setOrigin(32, 32);
	sprite.setPosition(pos);
}
void Projectile::draw() {
	// move towards destination
	sf::Vector2f newPos = destination - sprite.getPosition();
	if (abs(newPos.x) > abs(newPos.y)) {
		if (newPos.x > SPEED || newPos.x < -SPEED)
			newPos *= SPEED / abs(newPos.x);
	}
	else {
		if (newPos.y > SPEED || newPos.y < -SPEED)
			newPos *= SPEED / abs(newPos.y);
	}
	newPos += sprite.getPosition();
	sprite.setPosition(newPos);

	if (abs(destination.x - newPos.x) + abs(destination.y - newPos.y) <= 0.1f)
		reachedDestination = true;

	window.draw(sprite);
}