#include "EndGame.h"



EndGame::EndGame()
{
	font.loadFromFile("orange.ttf");
	text.setFont(font);
	text.setString("You have lost!");
	text.setFillColor(sf::Color::Red);
	text.setScale(1, 1);

	next.setFont(font);
	next.setString("Hit space if you want to play again");
	next.setFillColor(sf::Color::Cyan);
	next.setScale(1, 1);
}


EndGame::~EndGame()
{
}

bool EndGame::drawMenu(sf::RenderWindow &window) {
	window.clear();
	text.setPosition(sf::Vector2f(window.getSize().x / 2 - text.getLocalBounds().width / 2, window.getSize().y / 3));
	next.setPosition(sf::Vector2f(window.getSize().x / 2 - next.getLocalBounds().width / 2, window.getSize().y / 3 * 2));
	window.draw(text);
	window.draw(next);
	window.display();

	sf::Event event;
	while(window.isOpen())
	while (window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code) {
			case sf::Keyboard::Space:
				return true;
				break;
			case sf::Keyboard::Escape:
				return false;
			}
		}
	}
	return false;
}
