#pragma once
#include "SFML\Graphics.hpp"
#include "Enemy.h"
#include "Projectile.h"
#include <memory>

class Tower {

protected:

	sf::RenderWindow& window;
	sf::Texture baseTexture;
	sf::Texture overlayTexture;
	sf::Sprite baseSprite;
	sf::Sprite overlaySprite;
	sf::Texture outlineTexture;
	sf::Sprite outlineSprite;

	Enemy* target = nullptr;
	std::vector<std::shared_ptr<Enemy>>* aliveEnemies;
	std::vector<std::shared_ptr<Projectile>> projectiles;
	std::clock_t timeLastShot;
	sf::Texture firingTexture;
	sf::Sprite firingSpriteLeft;
	sf::Sprite firingSpriteRight;
	bool shootLeft;
	static const float SHOOTING_LENGTH;

public:

	sf::CircleShape rangeCircle;
	static Tower* selected;
	int type;
	int cost;
	float range;
	float damage;
	float attackSpeed;
	std::string name;
	sf::Vector2f pos;

	Tower(sf::RenderWindow& window, sf::Vector2f pos, int type, std::vector<std::shared_ptr<Enemy>>* aliveEnemies);
	void draw();
	void shoot();
	void handleTarget();
	void drawRange();

};
