#include "Paddle.h"



Paddle::Paddle(int width_, int height_)
{
	pad.loadFromFile("paddle.png");
	paddle.setTexture(pad);
	std::cout << pad.getSize().x << ", " << pad.getSize().y << std::endl;
	paddle.setScale(float(100) / pad.getSize().x, (float(15) / pad.getSize().y));
	//paddle.setSize(sf::Vector2f(width_ / 8, 15));
	//paddle.setFillColor(sf::Color::White);
	paddle.setPosition(width_ / 2 - 0.5 * width_ / 8, height_ - 15);
	width = width_ / 8;
	height = 15;
	x = width_ / 2 - 0.5 * width_ / 8;
	y = height_ - 15;
}


Paddle::~Paddle()
{
}


void Paddle::drawPaddle(sf::RenderWindow &window) {
	window.draw(paddle);
}

void Paddle::move(int x_) {
	if (paddle.getPosition().x + x_ <= 0) {
		paddle.setPosition(0, paddle.getPosition().y);
		x = 0;
	}
	else if (paddle.getPosition().x + x_ >= 7 * width) {
		paddle.setPosition(7 * width, paddle.getPosition().y);
		x = 7 * width;
	}
	else {
		paddle.move(x_, 0);
		x += x_;
	}
}

void Paddle::reset(int width_, int height_) {
	paddle.setPosition(width_ / 2 - 0.5 * width_ / 8, height_ - 15);
	width = width_ / 8;
	height = 15;
	x = width_ / 2 - 0.5 * width_ / 8;
	y = height_ - 15;
}


sf::Vector2f Paddle::getSize() const {
	sf::Vector2f size(width, height);
	return size;
}