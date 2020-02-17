#ifndef FIELD_H
#define FIELD_H
#include "SFML\Graphics.hpp"
#include <iostream>
#include "Ball.h"

struct block {
	int r;
	int g;
	int b;
	int hits_to_destroy;
	bool destroyed;
	sf::RectangleShape rect;
};

class Field
{
	int side_padding;
	int top_padding;
	int block_width;
	int block_height;
	int level;
	block **matrix;
	sf::Texture background_tex;
	sf::Sprite background_sprite;
	int columns;
	int rows;
	int window_width;
	//w zamysle po przejscicu danego lvla, zostaje wywolana metoda, ktora ustawi na nowo matrix wg nowego levela

public:
	Field(sf::RenderWindow &window);
	~Field();
	void drawField(sf::RenderWindow &window);
	//0 - brak kolizji, 1 - gora klocka, 2 - prawa strona klocka, 3 - dol klocka, 4 - lewa strona klocka, 5 - odbicie od jednej ze scian, 6 - odbicie od rakietki, 7 - utrata zycia
	int collision(Ball &ball, const Paddle &paddle);
	void reset(sf::RenderWindow &window);
};

#endif