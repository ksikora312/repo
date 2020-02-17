#ifndef GAME_H
#define GAME_H
#include "Ball.h"
#include "Paddle.h"
#include "Field.h"
#include "EndGame.h"

class Game
{
	sf::RenderWindow window;
	Field field;
	Paddle paddle;
	Ball ball;
	EndGame end;
	bool running;
	bool frame;
	int move_x;
	int move_y;
	int lifes;
	int ball_speed;

	sf::Clock clock;
	sf::Time frameTime;

	void reset();

public:
	Game();
	~Game();
	void run();
	void handleEvents();
};

#endif
