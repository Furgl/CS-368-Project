
#include "Tile.h"

Tile::Tile(sf::RenderWindow& window, sf::Texture* texture, sf::Vector2f drawingPos) 
: window(window) {
	sprite.setPosition(drawingPos);
	sprite.setTexture(*texture);
	sprite.setScale(sf::Vector2f(SIZE / 64.0f, SIZE / 64.0f));
}

void Tile::draw() {
	window.draw(sprite);
}
