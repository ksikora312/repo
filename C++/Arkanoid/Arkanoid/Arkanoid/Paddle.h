#ifndef PADDLE_H
#define PADDLE_H
#include "SFML\Graphics.hpp"

#include <iostream>

class Paddle
{
public:
	//sf::RectangleShape paddle;
	sf::Texture pad;
	sf::Sprite paddle;
	int x;
	int y;
	int width;
	int height;
	Paddle(int width_ = 800, int height_ = 600);
	~Paddle();
	void drawPaddle(sf::RenderWindow &window);
	void move(int x_);
	void reset(int width_ = 800, int height_ = 600);
	sf::Vector2f getSize() const;
};

#endif