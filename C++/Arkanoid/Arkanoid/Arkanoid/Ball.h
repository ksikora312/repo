#ifndef BALL_H
#define BALL_H
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Paddle.h"

class Ball
{
public:
	sf::CircleShape ball;
	Ball(const Paddle &p, int radius_ = 14);
	~Ball();
	void drawBall(sf::RenderWindow &window);
	void followPaddle(const Paddle &p);
	void start();
	void move();
	void changeX();
	void changeY();
	void drawLifes(sf::RenderWindow &window, int lifes);
	sf::Vector2f getPosition();
	int radius;
	int x_movement;
	int y_movement;
	bool moving;
	void operator()(const Paddle &paddle);
};

#endif

