#pragma once
#include "SFML\Graphics.hpp"
#include "Tile.h"
#include "HealthBar.h"
#include <cassert>
#include <memory>
#include <algorithm>

class Enemy {

private:

	// enemy textures
	sf::Texture enemy1;
	sf::Texture enemy2;
	sf::Texture enemy3;
	sf::Texture enemy4;
	sf::Texture enemy5;
	sf::Texture enemy6;

	sf::RenderWindow& window;
	std::vector<std::vector<int>>& map;

	sf::Sprite sprite;
	sf::Vector2f nextPos;
	sf::Vector2f finalPos;
	// random offset to make them look less uniform
	sf::Vector2f offset;
	int speed;
	double maxHealth;
	double currentHealth;
	HealthBar healthBar = HealthBar(window, sprite.getPosition().x, sprite.getPosition().y);

public:

	// true if killed by player or reached end of path
	bool isDead;
	// true if enemy reached end of the path and lives need to be updated
	bool reachedEnd;
	// how much money the player is given for killing this
	int value;

	Enemy(sf::RenderWindow& window, std::vector<std::vector<int>>& map,
		sf::Vector2f startPos, int type)
		: window(window), map(map) {
		isDead = false;
		reachedEnd = false;
		offset = sf::Vector2f(std::rand() % 40 - 20, std::rand() % 40 - 20);
		sprite.setScale(sf::Vector2f(Tile::SIZE / 64.0f, Tile::SIZE / 64.0f));
		sf::Vector2f pos = getDrawingPos(startPos);
		sprite.setPosition(pos);
		nextPos = pos;

		// initialize enemy according to type
		if (type == 1) {
			enemy1.loadFromFile("textures/enemy_1.png");
			sprite.setTexture(enemy1);
			speed = 20;
			maxHealth = 10;
			value = 1;
		}
		else if (type == 2) {
			enemy2.loadFromFile("textures/enemy_2.png");
			sprite.setTexture(enemy2);
			speed = 10;
			maxHealth = 20;
			value = 2;
		}
		else if (type == 3) {
			enemy3.loadFromFile("textures/enemy_3.png");
			sprite.setTexture(enemy3);
			speed = 10;
			maxHealth = 30;
			value = 3;
		}
		else if (type == 4) {
			enemy4.loadFromFile("textures/enemy_4.png");
			sprite.setTexture(enemy4);
			speed = 10;
			maxHealth = 40;
			value = 4;
		}
		else if (type == 5) {
			enemy5.loadFromFile("textures/enemy_5.png");
			sprite.setTexture(enemy5);
			speed = 5;
			maxHealth = 50;
			value = 5;
		}
		else if (type == 6) {
			enemy6.loadFromFile("textures/enemy_6.png");
			sprite.setTexture(enemy6);
			speed = 5;
			maxHealth = 60;
			value = 6;
		}
		
		sprite.setOrigin(32, 32);
		currentHealth = maxHealth;
	}

	void draw() {
		// move towards nextPos
		sf::Vector2f newPos = sprite.getPosition();
		float diffX = nextPos.x - newPos.x;
		float diffY = nextPos.y - newPos.y;
		if (diffX > 0)
			newPos.x += std::min((diffX / diffX) * (speed / 100.0f), diffX);
		else if (diffX < 0)
			newPos.x += std::max((diffX / -diffX) * (speed / 100.0f), diffX);
		if (diffY > 0)
			newPos.y += std::min((diffY / diffY) * (speed / 100.0f), diffY);
		else if (diffY < 0)
			newPos.y += std::max((diffY / -diffY) * (speed / 100.0f), diffY);
		sprite.setPosition(newPos);

		// reached end of path
		if (sprite.getPosition() == finalPos) {
			reachedEnd = true;
			isDead = true;
		}
		// if at nextPos, generate new nextPos
		else if (sprite.getPosition() == nextPos) {
			nextPos = getNextPath(getBoardPos(nextPos));
			// face the right direction
			if (sprite.getPosition().x > nextPos.x)
				sprite.setRotation(180); // left
			else if (sprite.getPosition().x < nextPos.x)
				sprite.setRotation(0);   // right
			else if (sprite.getPosition().y > nextPos.y)
				sprite.setRotation(270); // up
			else if (sprite.getPosition().y < nextPos.y)
				sprite.setRotation(90);  // down
		}

		// update healthBar pos with that of sprite
		healthBar.setPos(sprite.getPosition().x + offset.x, sprite.getPosition().y + offset.y);

		// apply random offset for drawing and remove afterwards
		sprite.setPosition(sprite.getPosition().x + offset.x, sprite.getPosition().y + offset.y);
		window.draw(sprite);
		sprite.setPosition(sprite.getPosition().x - offset.x, sprite.getPosition().y - offset.y);

		// draw healthbar only if currentHealth is below maxHealth and enemy is still alive
		if (currentHealth < maxHealth && !isDead)
			healthBar.draw();
	}

	// attack the enemy - reduce health, mark dead if needed, and update healthbar
	void attack(double damage) {
		currentHealth -= damage;
		if (currentHealth <= 0)
			isDead = true;
		else
			healthBar.update(currentHealth, maxHealth);
	}

	// get actual position on screen from a game tile's row and col
	static sf::Vector2f getDrawingPos(sf::Vector2f boardPos) {
		return sf::Vector2f(boardPos.y * Tile::SIZE, boardPos.x * Tile::SIZE + 100);
	}

	// not sure why the x and y are flipped in these two methods... but it works

	// get a game tile's row and col from actual position on screen
	static sf::Vector2f getBoardPos(sf::Vector2f drawingPos) {
		return sf::Vector2f((drawingPos.y - 100) / Tile::SIZE, drawingPos.x / Tile::SIZE);
	}

	// get next path location for enemy to move to based on map values
	sf::Vector2f getNextPath(sf::Vector2f boardPos) {
		std::vector<sf::Vector2f> paths;

		int row = boardPos.x;
		int col = boardPos.y;

		int maxRows = (int)map.size() - 1;
		int maxCols = (int)map[row].size() - 1;

		if (col > 0 && map[row][col - 1] > map[row][col]) // left
			paths.push_back(sf::Vector2f(row, col - 1));
		if (row > 0 && map[row - 1][col] > map[row][col]) // top
			paths.push_back(sf::Vector2f(row - 1, col));
		if (col < maxCols && map[row][col + 1] > map[row][col]) // right
			paths.push_back(sf::Vector2f(row, col + 1));
		if (row < maxRows && map[row + 1][col] > map[row][col]) // bottom
			paths.push_back(sf::Vector2f(row + 1, col));

		// end of path
		if (paths.size() == 0) {
			if (col == 0)
				paths.push_back(sf::Vector2f(row, col - 1)); // left
			else if (row == 0)
				paths.push_back(sf::Vector2f(row - 1, col)); // top
			else if (col == maxCols)
				paths.push_back(sf::Vector2f(row, col + 1)); // right
			else if (row == maxRows)
				paths.push_back(sf::Vector2f(row + 1, col)); // bottom
			finalPos = getDrawingPos(paths[0]);
			return finalPos;
		}

		sf::Vector2f path(getDrawingPos(paths[std::rand() % paths.size()]));
		return path;
	}

};
