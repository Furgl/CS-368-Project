#include "Stage.h"

const int Stage::TIME_BETWEEN_SPAWNS = 2;//3;

Stage::Stage(sf::RenderWindow& window, std::vector <int> map) : window(window), money(10), lives(10) {
	nextEnemy = 1;
	time = std::clock();

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
	bush_1.loadFromFile("textures/bush_1.png");
	bush_2.loadFromFile("textures/bush_2.png");
	bush_3.loadFromFile("textures/bush_3.png");
	bush_4.loadFromFile("textures/bush_4.png");
	rock_1.loadFromFile("textures/rock_1.png");
	rock_2.loadFromFile("textures/rock_2.png");
	rock_3.loadFromFile("textures/rock_3.png");
	shadow_1.loadFromFile("textures/shadow_1.png");
	shadow_2.loadFromFile("textures/shadow_2.png");
	shadow_3.loadFromFile("textures/shadow_3.png");
	grass_all.setSmooth(true);
	grass_none.setSmooth(true);
	grass_topRight.setSmooth(true);
	grass_topLeft.setSmooth(true);
	grass_bottomLeft.setSmooth(true);
	grass_bottomRight.setSmooth(true);
	grass_top.setSmooth(true);
	grass_left.setSmooth(true);
	grass_right.setSmooth(true);
	grass_bottom.setSmooth(true);
	grass_topAndLeft.setSmooth(true);
	grass_topAndRight.setSmooth(true);
	grass_bottomAndLeft.setSmooth(true);
	grass_bottomAndRight.setSmooth(true);
	bush_1.setSmooth(true);
	bush_2.setSmooth(true);
	bush_3.setSmooth(true);
	bush_4.setSmooth(true);
	rock_1.setSmooth(true);
	rock_2.setSmooth(true);
	rock_3.setSmooth(true);
	shadow_1.setSmooth(true);
	shadow_2.setSmooth(true);
	shadow_3.setSmooth(true);

	// put vector<int> map into vector<vector<int>> map
	this->map = std::vector<std::vector<int>>(10, std::vector<int>(12, 0));
	for (int i = 0; i < map.size(); ++i)
		this->map[i / 12][i % 12] = map[i];

	// initialize tiles
	tiles = std::vector<std::vector<Tile>>(10);
	for (int i = 0; i < map.size(); ++i) {
		int row = i / 12;
		int col = i % 12;
		if (this->map[row][col] == 2) {
			spawnPos.x = row;
			spawnPos.y = col;
		}
		tiles[row].push_back(Tile(window, getTexture(row, col), Enemy::getDrawingPos(sf::Vector2f(row, col))));
	}

	// create game board lines
	float space = Tile::SIZE;
	for (int row = 0; row <= (float)600 / space; ++row) {
		sf::RectangleShape line(sf::Vector2f(2, 500));
		line.setPosition(row*space, 100);
		lines.push_back(line);
	}
	for (int col = 0; col <= (float)500 / space; ++col) {
		sf::RectangleShape line(sf::Vector2f(600, 2));
		line.setPosition(0, col*space + 98);
		lines.push_back(line);
	}
}

int Stage::getCurrentWave() {
	return std::floor((nextEnemy - 1) / (waves.size() / numWaves));
}

int Stage::getTimeToNextWave() {
	if (getCurrentWave() == numWaves - 1)
		return 0;

	int enemiesPerWave = waves.size() / numWaves;
	int currentEnemyInWave = (nextEnemy - 1) % enemiesPerWave;
	return (enemiesPerWave - currentEnemyInWave - 1) * TIME_BETWEEN_SPAWNS + getTimeToNextEnemy();
}

int Stage::getTimeToNextEnemy() {
	double elapsedTime = (std::clock() - time) / CLOCKS_PER_SEC;
	return std::max(TIME_BETWEEN_SPAWNS - elapsedTime, 0.0);
}

void Stage::draw() {
	// spawn the next enemy if TIME_BETWEEN_SPAWNS seconds have passed
	if (nextEnemy < waves.size()) {
		if (getTimeToNextEnemy() == 0) {
			if (waves[nextEnemy] > 0)
				aliveEnemies.push_back(std::make_unique<Enemy>(
					window, map, spawnPos, waves[nextEnemy]));
			nextEnemy++;
			time = std::clock();
		}
	}

	// draw tiles
	for (std::vector<Tile> tileVec : tiles)
		for (Tile tile : tileVec)
			tile.draw();

	// draw lines
	sf::Uint8 fade = abs(cos(main::counter * (double) 0.0004) * 80);
	for (sf::RectangleShape line : lines) {
		line.setFillColor(sf::Color(100, 150, 210, 20 + fade));
		window.draw(line);
	}

	// draw decorations
	for (sf::Sprite sprite : decorations)
		window.draw(sprite);

	// remove dead enemies and deal with them appropriately
	aliveEnemies.erase(std::remove_if(aliveEnemies.begin(), aliveEnemies.end(),
		[this](std::shared_ptr<Enemy> enemy) {
		if (enemy->isDead) {
			if (enemy->reachedEnd)
				--lives;
			else
				money += enemy->value;
			return true;
		}
		return false;
	}), aliveEnemies.end());

	// draw enemies that are alive
	for (std::shared_ptr<Enemy> enemy : aliveEnemies)
		enemy->draw();

	// draw towers
	for (std::vector<Tile> tileVec : tiles)
		for (Tile tile : tileVec)
			if (tile.tower != nullptr)
				tile.tower->draw();

	// draw tower range circles
	for (std::vector<Tile> tileVec : tiles)
		for (Tile tile : tileVec)
			if (tile.tower != nullptr)
				tile.tower->drawRange();
}

// get texture of tile in map based on neighboring numbers in map
sf::Texture* Stage::getTexture(int row, int col) {

	if (map[row][col] == 0)
		return &grass_all;

	int maxRows = (int)map.size() - 1;
	int maxCols = (int)map[row].size() - 1;

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