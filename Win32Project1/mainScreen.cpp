#include "mainScreen.h"
#include "cScreen.h"
#include "SFML\Graphics.hpp"
#include "Button.h"
#include "ButtonExit.h"
#include "ButtonPlay.h"

int mainScreen::Run(sf::RenderWindow &window)
{
	sf::Texture texture;
	if (!texture.loadFromFile("textures/title_background.jpg"))
		window.close(); // error
	sf::Sprite background;
	background.setTexture(texture);
	background.setTextureRect(sf::IntRect(25, 0, window.getSize().x, window.getSize().y));
	background.setScale(sf::Vector2f(1.25f, 1.25f));

	// load font
	sf::Font font;
	if (!font.loadFromFile("fonts/airstrike.ttf"))
		window.close(); // error

						// create title text
	sf::Text title;
	title.setFont(font);
	title.setString("Tower Defense");
	title.setCharacterSize(70);
	title.setFillColor(sf::Color::Blue);
	title.setStyle(sf::Text::Bold | sf::Text::Underlined);
	title.setPosition(sf::Vector2f(window.getSize().x / 2 - title.getLocalBounds().width / 2, 150));
	title.setOutlineThickness(3);
	title.setOutlineColor(sf::Color(40, 100, 200));

	// create vector of current buttons
	std::vector<Button*> buttons;
	buttons.push_back(new ButtonExit(window, font, 480, 342));
	buttons.push_back(new ButtonPlay(window, font, 190, 342));

	// for fading
	double counter = 0;

	// run program as long as window is open
	while (true) {

		// clear the window with black color
		window.clear(sf::Color::Black);

		// fade background, just for fun
		counter += 0.0002;
		sf::Uint8 fade = abs(cos(counter) * 80) + 130;
		background.setColor(sf::Color(fade, fade, fade));

		// process events
		sf::Event event;
		while (window.pollEvent(event)) {

			// mouse moved - update buttons
			if (event.type == sf::Event::MouseMoved) {
				for (Button* button : buttons)
					button->isMouseOver(event.mouseMove.x, event.mouseMove.y);
			}

			// mouse click - update buttons
			else if (event.type == sf::Event::MouseButtonPressed &&
				event.mouseButton.button == sf::Mouse::Left) {
				for (Button* button : buttons)
					if (button->isMouseOver(event.mouseButton.x, event.mouseButton.y))
						return button->onClick();
			}

			// close window when requested
			else if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		// draw everything here
		window.draw(background);
		window.draw(title);
		for (Button* button : buttons)
			button->draw();

		// end current frame
		window.display();
	}

	return -1;
}