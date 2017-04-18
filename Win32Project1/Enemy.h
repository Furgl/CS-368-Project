#pragma once
#include "SFML\Graphics.hpp"
#include "Tile.h"
#include "HealthBar.h"
#include <cassert>
#include <memory>
#include <algorithm>

class Enemy {

private:
	
	sf::Texture enemy1;

	sf::RenderWindow& window;
	std::vector<std::vector<int>>& map;

	sf::Sprite sprite;
	sf::Vector2f nextPos;
	sf::Vector2f finalPos;
	int speed;
	double health;
	HealthBar healthBar = HealthBar(window, sprite.getPosition().x, sprite.getPosition().y);


public:

	// true if killed by player or reached end of path
	bool isDead;
	// true if enemy reached end of the path and lives need to be updated
	bool reachedEnd;
	// how much money the player is given for killing this
	int value;

	//Not exactly sure how we wanna do hit mechanics but for now if hit set this flag to true to update health;
	bool wasHit;


	Enemy(sf::RenderWindow& window, std::vector<std::vector<int>>& map,
		sf::Vector2f startPos, int type)	
		: window(window), map(map) {
		isDead = false;
		reachedEnd = false;
		wasHit = false;
		sprite.setScale(sf::Vector2f(Tile::SIZE / 64.0f, Tile::SIZE / 64.0f));
		sf::Vector2f pos = getDrawingPos(startPos);
		sprite.setPosition(pos);
		nextPos = getNextPath(startPos);

		// initialize enemy according to type
		if (type == 1) {
			enemy1.loadFromFile("textures/enemy_1.png");
			sprite.setTexture(enemy1);
			sprite.setOrigin(enemy1.getSize().x/2, enemy1.getSize().y/2);
			speed = 30;
			health = 10;
			value = 1;
		}
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

		//update healthBar pos with that of sprite
		healthBar.setPos(sprite.getPosition().x, sprite.getPosition().y);
		

		//SIMPLY HERE TO TEST IF THE HIT FUNCTION IN HEALTH BAR IS WORKING
		//Press and hold Spacebar to see health decrease
			sf::Event event;
			int dead = 0;

			while (window.pollEvent(event)) {

				if (event.type == sf::Event::KeyPressed) {

					if (event.key.code == sf::Keyboard::Space) {
						dead = healthBar.hit(1, health);
						health -= 1;
					}
					if (dead == 1)
						isDead = true;
				}
			}
		

		window.draw(sprite);
		if (dead != 1)
			healthBar.draw();
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
