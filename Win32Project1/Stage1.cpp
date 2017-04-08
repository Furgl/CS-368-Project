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
) {}
