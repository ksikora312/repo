#include "Game.h"



Game::Game() :window(sf::VideoMode(800, 600), "Arkanoid"), paddle(int(window.getSize().x), int(window.getSize().y)), ball(paddle), field(window)
{
	running = true;
	frame = true;
	ball_speed = 300;
	frameTime = sf::milliseconds(1000 / ball_speed);
	move_x = 1;
	move_y = -1;
	lifes = 3;
}


Game::~Game()
{
}

void Game::run() {
	while (running) {
	if (frame) {
		clock.restart();
		window.clear();
		field.drawField(window);
		paddle.drawPaddle(window);
		ball.drawBall(window);
		ball.drawLifes(window, lifes);
		window.display();
		frame = false;
	}
		handleEvents();
		sf::Time time = clock.getElapsedTime();
		if (time.asMilliseconds() >= frameTime.asMilliseconds()) {
			if (ball.moving) {
				int colision = field.collision(ball, paddle);
				//std::cout << move_x << ", " << move_y << std::endl;
				ball.move();
				if (colision == 7) {
					lifes--;
					if (lifes <= 0) {
						if (end.drawMenu(window)) {
							reset();
							lifes = 3;
						}
						else
							window.close();
					}
					ball(paddle);
				}
			}
			frame = true;
		}
	}
}

void Game::handleEvents() {

	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed:
				window.close();
			case sf::Event::KeyPressed:
				switch (event.key.code) {
					case sf::Keyboard::Left:
						paddle.move(-10);
						ball.followPaddle(paddle);
						break;
					case sf::Keyboard::Right:
						paddle.move(10);
						ball.followPaddle(paddle);
						break;
					case sf::Keyboard::Space:
						if (ball.moving == false) {
							ball.start();
						}
				}
		}
	}
}


void Game::reset() {
	paddle.reset(window.getSize().x, window.getSize().y);
	ball(paddle);
	field.reset(window);
}