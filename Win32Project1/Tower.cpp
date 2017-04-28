#include "Tower.h"
#include <cmath>

const double PI = std::acos(-1);
const float Tower::SHOOTING_LENGTH = 0.3f;
Tower* Tower::selected = nullptr;

Tower::Tower(sf::RenderWindow& window, sf::Vector2f pos, int type, std::vector<std::shared_ptr<Enemy>>* aliveEnemies)
	: window(window), type(type), aliveEnemies(aliveEnemies) {
	sf::Vector2f offset(-6, -8);
	this->pos = sf::Vector2f(pos.x + offset.x, pos.y + offset.y);

	timeLastShot = 0;
	shootLeft = true;

	outlineTexture.loadFromFile("textures/tower_outline.png");
	outlineSprite.setTexture(outlineTexture);
	outlineSprite.setPosition(this->pos);

	baseTexture.loadFromFile("textures/tower_base.png");
	baseTexture.setSmooth(true);
	baseSprite.setTexture(baseTexture);
	baseSprite.setPosition(this->pos);

	overlaySprite.setScale(sf::Vector2f(50 / 64.0f, 50 / 64.0f));
	overlaySprite.setPosition(sf::Vector2f(this->pos.x + 32, this->pos.y + 32));
	overlaySprite.setOrigin(32, 32);

	firingTexture.loadFromFile("textures/tower_fire.png");
	firingSpriteLeft.setTexture(firingTexture);
	firingSpriteLeft.setPosition(sf::Vector2f(this->pos.x + 32, this->pos.y + 32));
	firingSpriteRight.setTexture(firingTexture);
	firingSpriteRight.setPosition(sf::Vector2f(this->pos.x + 32, this->pos.y + 32));

	switch (type) {
	case 1:
		name = "Turret";
		cost = 5;
		range = 2;
		damage = 1;
		attackSpeed = 4;
		overlayTexture.loadFromFile("textures/tower_1.png");
		firingSpriteLeft.setOrigin(32, 67);
		break;
	case 2:
		name = "Adv. Turret";
		cost = 10;
		range = 3;
		damage = 2;
		attackSpeed = 5;
		overlayTexture.loadFromFile("textures/tower_2.png");
		firingSpriteLeft.setOrigin(37, 67);
		firingSpriteRight.setOrigin(27, 67);
		break;
	case 3:
		name = "Minigun";
		cost = 15;
		range = 4;
		damage = 1;
		attackSpeed = 12;
		overlayTexture.loadFromFile("textures/tower_3.png");
		firingSpriteLeft.setOrigin(37, 64);
		firingSpriteRight.setOrigin(27, 64);
		break;
	case 4:
		name = "Missile Launcher";
		cost = 20;
		range = 5;
		damage = 15;
		attackSpeed = 1;
		overlayTexture.loadFromFile("textures/tower_4.png");
		break;
	}

	rangeCircle.setFillColor(sf::Color(100, 100, 255, 30));
	rangeCircle.setOutlineThickness(5);
	rangeCircle.setOutlineColor(sf::Color(100, 100, 255, 150));
	rangeCircle.setRadius(range * 50 + 25);
	rangeCircle.setPosition(this->pos.x + 32 - rangeCircle.getRadius(), this->pos.y + 32 - rangeCircle.getRadius());

	overlayTexture.setSmooth(true);
	overlaySprite.setTexture(overlayTexture);
}

void Tower::draw() {
	handleTarget();
	shoot();
	// remove projectiles at their destinations and damage the target
	// (only damages current target, not necessarily the projectile's target -
	//  so we don't have to deal with a situation where the projectile's target
	//  is removed before the projectile reaches it)
	projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
		[this](std::shared_ptr<Projectile> projectile) {
		if (projectile->reachedDestination) {
			if (target != nullptr)
				target->attack(damage);
			return true;
		}
		return false;
	}), projectiles.end());

	// draw base, overlay, and projectiles
	window.draw(baseSprite);
	for (auto i = projectiles.begin(); i < projectiles.end(); ++i)
		(*i).get()->draw();
	if (type != 4)
		window.draw(overlaySprite);

	// draw firing sprite
	double elapsedTime = (std::clock() - timeLastShot) / (float) CLOCKS_PER_SEC;
	if (elapsedTime <= SHOOTING_LENGTH) {
		firingSpriteLeft.setRotation(overlaySprite.getRotation());
		firingSpriteRight.setRotation(overlaySprite.getRotation());
		switch (type) {
		case 1:
			window.draw(firingSpriteLeft);
			break;
		case 2:
			if (shootLeft)
				window.draw(firingSpriteLeft);
			else
				window.draw(firingSpriteRight);
			break;
		case 3:
			if (shootLeft)
				window.draw(firingSpriteLeft);
			else
				window.draw(firingSpriteRight);
			break;
		}
	}
	else if (type == 4)
		window.draw(overlaySprite);
}

void Tower::shoot() {
	if (target != nullptr) {
		double elapsedTime = (std::clock() - timeLastShot) / (float) CLOCKS_PER_SEC;
		if (elapsedTime >= (2 / attackSpeed)) {
			timeLastShot = std::clock();
			shootLeft = !shootLeft;

			sf::Vector2f targetPos = target->sprite.getPosition();
			targetPos.x += target->offset.x;
			targetPos.y += target->offset.y;
			projectiles.push_back(std::make_shared<Projectile>(Projectile(window, type, overlaySprite.getPosition(), targetPos, overlaySprite.getRotation())));
		}
	}
}

// remove out of range target, look for new one, and/or rotate to face target
void Tower::handleTarget() {
	if (aliveEnemies != nullptr) {
		// if target is out of range, remove it
		if (target != nullptr) {
			sf::Vector2f targetPos = target->sprite.getPosition();
			targetPos.x += target->offset.x;
			targetPos.y += target->offset.y;
			float distance = sqrt(pow(targetPos.x - overlaySprite.getPosition().x, 2) + pow(targetPos.y - overlaySprite.getPosition().y, 2));
			if (distance > rangeCircle.getRadius())
				target = nullptr;
		}

		// if tower doesn't have a target, look for one
		if (target == nullptr) {
			for (std::shared_ptr<Enemy> enemy : *aliveEnemies) {
				sf::Vector2f enemyPos = enemy->sprite.getPosition();
				enemyPos.x += enemy->offset.x;
				enemyPos.y += enemy->offset.y;
				float distance = sqrt(pow(enemyPos.x - overlaySprite.getPosition().x, 2) + pow(enemyPos.y - overlaySprite.getPosition().y, 2));
				if (distance <= rangeCircle.getRadius()) {
					target = enemy.get();
					break;
				}
			}
		}

		// rotate to target
		if (target != nullptr) {
			sf::Vector2f targetPos = target->sprite.getPosition();
			targetPos.x += target->offset.x;
			targetPos.y += target->offset.y;
			float dx = pos.x + 32 - targetPos.x;
			float dy = pos.y + 32 - targetPos.y;
			float rotation = (atan2(dy, dx)) * 180 / PI - 90;
			overlaySprite.setRotation(rotation);
		}
	}
}

// draw circle around tower when selected representing its attack range
void Tower::drawRange() {
	if (selected == this) {
		window.draw(rangeCircle);
		draw();
		window.draw(outlineSprite);
	}
}