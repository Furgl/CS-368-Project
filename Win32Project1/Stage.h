#pragma once

#include <vector>
#include <random>
#include <cassert>
#include "Tile.h"

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

	sf::RenderWindow& window;
	// 0 represents terrain, while numbers > 0 represent the path
	// 1 is a normal path block
	// numbers > 1 are paths that enemies will take (they will render at the top left of the path) 
	// Enemies will only be able to move to tiles with higher numbers
	std::vector<std::vector<int>> map;
	// Tile objects corresponding to [row][col] of game board
	std::vector<std::vector<Tile>> tiles;

public:

	Stage(sf::RenderWindow& window, std::vector <int> map) : window(window) {
		// initialize textures
		grass_all.loadFromFile("textures/grass_all.png");
		grass_none.loadFromFile("textures/grass_none.png");
		grass_topRight.loadFromFile("textures/grass_topRight.png");
		grass_topLeft.loadFromFile("textures/grass_topLeft.png");
		grass_bottomLeft.loadFromFile("textures/grass_bottomLeft.png");
		grass_bottomRight.loadFromFile("textures/grass_bottomRight.png");
		grass_top.loadFromFile("textures/grass_top.png");
		grass_left.loadFromFile("textures/grass_left.png");
		grass_right.loadFromFile("textures/grass_right.png");
		grass_bottom.loadFromFile("textures/grass_bottom.png");
		grass_topAndLeft.loadFromFile("textures/grass_topAndLeft.png");
		grass_topAndRight.loadFromFile("textures/grass_topAndRight.png");
		grass_bottomAndLeft.loadFromFile("textures/grass_bottomAndLeft.png");
		grass_bottomAndRight.loadFromFile("textures/grass_bottomAndRight.png");

		// put vector<int> map into vector<vector<int>> map
		this->map = std::vector<std::vector<int>>(10, std::vector<int>(12, 0));
		for (int i = 0; i < map.size(); ++i)
			this->map[i / 12][i % 12] = map[i];

		// initialize tiles
		tiles = std::vector<std::vector<Tile>>(10);
		for (int i = 0; i < map.size(); ++i) {
			int row = i / 12;
			int col = i % 12;
			tiles[row].push_back(Tile(window, getTexture(row, col), getDrawingPos(row, col)));
		}
	}

	// get actual position on screen from a game tile's row and col
	sf::Vector2f getDrawingPos(int row, int col) {
		return sf::Vector2f(col * Tile::SIZE, row * Tile::SIZE + 100);
	}

	// get next path location for enemy to move to based on map values
	sf::Vector2f getNextPath(int row, int col) {
		std::vector<sf::Vector2f> paths;

		int maxRows = (int)map.size() - 1;
		int maxCols = (int)map[row].size() - 1;

		if (col == 0 || (col > 0 && map[row][col - 1] > map[row][col])) // left
			paths.push_back(sf::Vector2f(row, col - 1));
		if (row == 0 || (row > 0 && map[row - 1][col] > map[row][col])) // top
			paths.push_back(sf::Vector2f(row - 1, col));
		if (row == maxRows || (row < maxRows && map[row][col + 1] > map[row][col])) // right
			paths.push_back(sf::Vector2f(row, col + 1));
		if (col == maxCols || (col < maxCols && map[row + 1][col] > map[row][col])) // bottom
			paths.push_back(sf::Vector2f(row + 1, col));

		assert(paths.size() > 0); // safety check - should never happen if map is set up correctly

		return paths[std::rand() % paths.size()];
	}

	void draw() {
		for (std::vector<Tile> tileVec : tiles)
			for (Tile tile : tileVec)
				tile.draw();
	}

	// get texture of tile in map based on neighboring numbers in map
	sf::Texture* Stage::getTexture(int row, int col) {
		
		if (map[row][col] == 0)
			return &grass_all;

		int maxRows = (int)map.size()-1;
		int maxCols = (int)map[row].size()-1;

		int left = col > 0 ? map[row][col - 1] : 1;
		int topLeft = col > 0 && row > 0 ? map[row - 1][col - 1] : 1;
		int top = row > 0 ? map[row - 1][col] : 1;
		int topRight = row > 0 && col < maxCols ? map[row - 1][col + 1] : 1;
		int right = col < maxCols ? map[row][col + 1] : 1;
		int bottomRight = col < maxCols && row < maxRows ? map[row + 1][col + 1] : 1;
		int bottom = row < maxRows ? map[row + 1][col] : 1;
		int bottomLeft = col > 0 && row < maxRows ? map[row + 1][col - 1] : 1;

		if (top == 0)
			if (left == 0)
				return &grass_topAndLeft;
			else if (right == 0)
				return &grass_topAndRight;
			else
				return &grass_top;
		else if (bottom == 0)
			if (left == 0)
				return &grass_bottomAndLeft;
			else if (right == 0)
				return &grass_bottomAndRight;
			else
				return &grass_bottom;
		else if (left == 0)
			return &grass_left;
		else if (right == 0)
			return &grass_right;
		else if (topRight == 0)
			return &grass_topRight;
		else if (topLeft == 0)
			return &grass_topLeft;
		else if (bottomLeft == 0)
			return &grass_bottomLeft;
		else if (bottomRight == 0)
			return &grass_bottomRight;
		else 
			return &grass_none;
	}

};