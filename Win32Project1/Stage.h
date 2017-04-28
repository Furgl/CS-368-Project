#pragma once

#include <vector>
#include <random>
#include <memory>
#include "Tile.h"
#include "Enemy.h"
#include "main.h"
#include <ctime>

class Stage {

protected:

	// textures (will probably be put into vector organized by path and terrain type)
	sf::Texture grass_all;
	sf::Texture grass_none;
	sf::Texture grass_topRight;
	sf::Texture grass_topLeft;
	sf::Texture grass_bottomLeft;
	sf::Texture grass_bottomRight;
	sf::Texture grass_top;
	sf::Texture grass_left;
	sf::Texture grass_right;
	sf::Texture grass_bottom;
	sf::Texture grass_topAndRight;
	sf::Texture grass_topAndLeft;
	sf::Texture grass_bottomAndRight;
	sf::Texture grass_bottomAndLeft;

	// decoration textures
	sf::Texture bush_1;
	sf::Texture bush_2;
	sf::Texture bush_3;
	sf::Texture bush_4;
	sf::Texture rock_1;
	sf::Texture rock_2;
	sf::Texture rock_3;
	sf::Texture shadow_1;
	sf::Texture shadow_2;
	sf::Texture shadow_3;

	sf::RenderWindow& window;
	// Lines outline the game board tiles
	std::vector<sf::RectangleShape> lines;
	// Decorations for the map (bushes, rocks, shadows)
	std::vector<sf::Sprite> decorations;
	// Row and column where enemies will spawn at, marked as a 2 on the map
	sf::Vector2f spawnPos;
	// Used for timing between enemy spawns
	std::clock_t time;

public:

	// 0 represents terrain, while numbers > 0 represent the path
	// 1 is a normal path block
	// numbers > 1 are paths that enemies will take (they will render at the top left of the path) 
	// Enemies will only be able to move to tiles with higher numbers
	std::vector<std::vector<int>> map;
	// Tile objects corresponding to [row][col] of game board
	std::vector<std::vector<Tile>> tiles;
	// Time between each enemy spawning in each wave in seconds
	static const int TIME_BETWEEN_SPAWNS;
	// Number of waves on this stage
	int numWaves;
	// Index for moving through waves
	int nextEnemy;
	// Enemies that have not yet spawned, 0 for none
	std::vector<int> waves;
	// Enemies that are currently on the board
	std::vector<std::shared_ptr<Enemy>> aliveEnemies;

	int money;
	int lives;

	Stage(sf::RenderWindow& window, std::vector <int> map);
	int getCurrentWave();
	int getTimeToNextWave();
	int getTimeToNextEnemy();
	void draw();
	sf::Texture* Stage::getTexture(int row, int col);

};