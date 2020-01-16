#include "Ball.h"



Ball::Ball(const Paddle &p, int radius_) :ball(radius_)
{
	radius = radius_;
	ball.setFillColor(sf::Color(255, 255, 255));
	//pozycja na prostokacie odbijajacym pilke
	//ball.setPosition()
	ball.setOutlineColor(sf::Color::Cyan);
	ball.setOutlineThickness(2);
	ball.setPosition(p.x - radius + p.width / 2, p.y - 2 * radius - ball.getOutlineThickness());
	//radius = radius_ + ball.getOutlineThickness();
	moving = false;
	x_movement = 1;
	y_movement = -1;
}


Ball::~Ball()
{
}

void Ball::drawBall(sf::RenderWindow &window) {
	window.draw(ball);
}


void Ball::followPaddle(const Paddle &p) {
	if (!moving) {
		ball.setPosition(p.x - radius + p.width / 2, p.y - 2 * radius - ball.getOutlineThickness());
		ball.setPosition(p.x - radius + p.width / 2, p.y - 2 * radius - ball.getOutlineThickness());
	}
}

void Ball::start() {
	moving = true;
	std::cout << ball.getPosition().x << ", " << ball.getPosition().y << std::endl;
}


void Ball::move() {
	ball.move(x_movement, y_movement);
}

sf::Vector2f Ball::getPosition() {
	return ball.getPosition();
}

void Ball::changeX() {
	if (x_movement == 1)
		x_movement = -1;
	else
		x_movement = 1;
}

void Ball::changeY() {
	if (y_movement == 1)
		y_movement = -1;
	else
		y_movement = 1;
}

void Ball::operator()(const Paddle &paddle) {
	moving = false;
	x_movement = 1;
	y_movement = -1;
	followPaddle(paddle);

}

void Ball::drawLifes(sf::RenderWindow &window, int lifes) {
	sf::CircleShape bal = ball;
	bal.setScale(0.5, 0.5);
	for (int i = 0; i < lifes; i++) {
		bal.setPosition(5 + 3 * i + i*bal.getRadius(), 5);
		window.draw(bal);
	}
}
