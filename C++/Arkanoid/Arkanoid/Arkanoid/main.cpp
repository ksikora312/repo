#include <SFML/Graphics.hpp>
#include "Field.h"
#include "Ball.h"
#include "Paddle.h"
#include "Game.h"

int main() {

	/*
	sf::RenderWindow window(sf::VideoMode(800, 600), "Arcanoid");
	Field f;
	Paddle p;
	Ball b(p);
	window.clear();
	f.drawField(window);
	b.drawBall(window);
	p.drawPaddle(window);
	window.display();
	system("PAUSE");
	*/

	Game game;
	game.run();
	/*

	sf::RenderWindow window(sf::VideoMode(500, 500), "GOWNO");
	window.clear();
	sf::RectangleShape rect;
	rect.setPosition(100, 100);
	rect.setSize(sf::Vector2f(100, 100));
	rect.setFillColor(sf::Color::Cyan);
	sf::CircleShape circ;
	circ.setPosition(300, 300);
	circ.setRadius(30);
	circ.setFillColor(sf::Color::Green);
	window.draw(circ);
	sf::Time t;
	t = sf::milliseconds(100);
	for (int i = 0; i < 20; i++) {
		window.clear();
		circ.move(5, -5);
		window.draw(circ);
		window.display();
		sf::sleep(t);
	}
	//window.draw(rect);
	//window.display();
	t = sf::milliseconds(5000);
	sf::sleep(t);
	*/

	return 0;
}