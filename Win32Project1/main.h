#pragma once

#include <SFML/Graphics.hpp>
#include "Screen.h"

class main {

public:

	// 0 is title, 1 is game
	static int currentScreen;
	static std::vector<Screen*> screens;
	static double counter;

};