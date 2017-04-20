#include "Stage1.h"

Stage1::Stage1(sf::RenderWindow& window) : Stage(window, 
	// (may be a little confusing to understand at first)
	// readable/easily editable map representing the game board 
	// 0 represents terrain, while numbers > 0 represent the path
	// 1 is a normal path block
	// numbers > 1 are paths that enemies will take (they will render at the top left of the path) 
	// Enemies will only be able to move to tiles with higher numbers
  { 0,  1,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  1,  3,  0,  0,  1,  1,  1,  1,  1,  1,  0,
	0,  1,  4,  0,  0,  1, 12, 13, 14, 15, 16,  0,
	0,  1,  5,  1,  1,  1, 11,  0,  0,  1, 17,  0,
	0,  1,  6,  7,  8,  9, 10,  0,  0,  1, 18,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  1, 19,  0,
	0,  1,  1,  1,  1,  1,  1,  0,  0,  1, 20,  0,
	0,  1, 31, 30, 29, 28, 27,  1,  1,  1, 21,  0,
	0,  1, 32,  0,  0,  1, 26, 25, 24, 23, 22,  0,
	0,  1, 33,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
) {
	numWaves = 6;
	// typically should have the last few enemies in a wave be 0
	// so that there's time to prepare before the next wave starts
	// first wave should also be all 0 so player can prepare
	// 1-6 are types of enemies that will spawn, 0 is nothing
	// each row represents a wave
	waves = {
		0,0,0,0,0,0,0,0,0,0,
		1,1,1,2,1,2,0,0,0,0,
		3,1,1,2,1,3,0,0,0,0, 
		2,3,2,4,0,1,0,0,0,0,
		5,0,0,5,0,2,0,0,0,0,
		5,6,0,1,1,4,0,0,0,0
	};

	// add decorations
	sf::Sprite sprite;

	sprite.setTexture(bush_1);
	sprite.setPosition(sf::Vector2f(20, 376));
	sprite.setRotation(30);
	decorations.push_back(sprite);

	sprite.setTexture(bush_3);
	sprite.setPosition(sf::Vector2f(300, 100));
	sprite.setRotation(30);
	decorations.push_back(sprite);

	sprite.setTexture(bush_4);
	sprite.setPosition(sf::Vector2f(360, 364));
	sprite.setRotation(12);
	decorations.push_back(sprite);

	sprite.setTexture(rock_1);
	sprite.setPosition(sf::Vector2f(520, 310));
	sprite.setRotation(0);
	decorations.push_back(sprite);

	sprite.setTexture(shadow_1);
	sprite.setPosition(sf::Vector2f(62, 223));
	sprite.setRotation(10);
	decorations.push_back(sprite);

	sprite.setTexture(shadow_2);
	sprite.setPosition(sf::Vector2f(155, 505));
	sprite.setRotation(5);
	decorations.push_back(sprite);

	sprite.setTexture(shadow_3);
	sprite.setPosition(sf::Vector2f(289, 483));
	sprite.setRotation(5);
	decorations.push_back(sprite);
}
