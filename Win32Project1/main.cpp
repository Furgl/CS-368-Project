#include "main.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h> 
#include <time.h>
#include "ScreenGame.h"
#include "ScreenTitle.h"

// 0 is title, 1 is game
int main::currentScreen = 0;
std::vector<Screen*> main::screens;
double main::counter = 0;

int WinMain() {
	// set anti aliasing
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	// create window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Tower Defense", sf::Style::Close, settings);

	// create screens
	ScreenTitle title(window);
	main::screens.push_back(&title);
	ScreenGame game(window);
	main::screens.push_back(&game);

	// run program as long as window is open - handles all screen buttons and calls Screen#run()
	while (window.isOpen()) {

		// clear the window with black color
		window.clear(sf::Color::Black);

		// process events
		sf::Event event;
		while (window.pollEvent(event)) {

			// SIMPLY HERE TO TEST IF THE HIT FUNCTION IN HEALTH BAR IS WORKING
			// Press and hold Spacebar to see health decrease
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
				main::screens[main::currentScreen]->spacebar();


			// mouse moved - update buttons
			if (event.type == sf::Event::MouseMoved) {
				for (Button* button : main::screens[main::currentScreen]->buttons)
					button->isMouseOver(event.mouseMove.x, event.mouseMove.y);
			}

			// mouse click - update buttons
			else if (event.type == sf::Event::MouseButtonPressed &&
				event.mouseButton.button == sf::Mouse::Left) {
				for (Button* button : main::screens[main::currentScreen]->buttons)
					if (button->isMouseOver(event.mouseButton.x, event.mouseButton.y))
						button->onClick();
			}

			// close window when requested
			else if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		// used for fading
		main::counter++;

		// draw buttons and call Screen#run()
		main::screens[main::currentScreen]->draw();
		for (Button* button : main::screens[main::currentScreen]->buttons)
			button->draw();

		// end current frame
		window.display();
	}

	return EXIT_SUCCESS;
}