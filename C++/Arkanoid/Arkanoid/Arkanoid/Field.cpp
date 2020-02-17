#include "Field.h"



Field::Field(sf::RenderWindow &window)
{
	level = 1;
	columns = 6;
	rows = 5;
	matrix = new block *[rows];
	for (int i = 0; i < columns; i++) {
		matrix[i] = new block[columns];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (i == 0) {
				matrix[i][j].r = 255;
				matrix[i][j].g = 0;
				matrix[i][j].b = 0;
			}
			else if (i == 1) {
				matrix[i][j].r = 0;
				matrix[i][j].g = 255;
				matrix[i][j].b = 255;
			}
			else if (i == 2) {
				matrix[i][j].r = 0;
				matrix[i][j].g = 0;
				matrix[i][j].b = 235;
			}
			else if (i == 3) {
				matrix[i][j].r = 255;
				matrix[i][j].g = 0;
				matrix[i][j].b = 0;
			}
			else {
				matrix[i][j].r = 0;
				matrix[i][j].g = 225;
				matrix[i][j].b = 0;
			}
			matrix[i][j].hits_to_destroy = 1;
			matrix[i][j].destroyed = false;
		}
	}
	side_padding = 50;
	top_padding = 50;
	int x_size_for_all_blocks = window.getSize().x - side_padding * 2 - ((columns - 1) * 10);
	int y_size_for_all_blocks = (window.getSize().y / 5);
	block_width = x_size_for_all_blocks / columns;
	block_height = y_size_for_all_blocks / rows;
	window_width = window.getSize().x;
	background_tex.loadFromFile("background.jpg");
	background_sprite.setTexture(background_tex);
	background_sprite.setPosition(0, 0);
	float scale_x;
	float scale_y;
	scale_x = background_tex.getSize().x;
	scale_y = background_tex.getSize().y;
	//std::cout << scale_x << ", " << scale_y << std::endl;
	background_sprite.setScale(800 / scale_x, 600 / scale_y);
}


Field::~Field()
{
}

void Field::drawField(sf::RenderWindow &window) {
	int x_size_for_all_blocks = window.getSize().x - side_padding * 2 - ((columns - 1) * 10);
	int y_size_for_all_blocks = (window.getSize().y / 5);
	int x = x_size_for_all_blocks / columns;
	int y = y_size_for_all_blocks / rows;
	sf::RectangleShape rect;
	sf::Vector2f size;
	size.x = x;
	size.y = y;
	window.draw(background_sprite);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (!matrix[i][j].destroyed) {
				rect.setSize(size);
				rect.setPosition(side_padding + (j * x) + j * 10, top_padding + i * y + i * 5);
				rect.setFillColor(sf::Color(matrix[i][j].r, matrix[i][j].g, matrix[i][j].b));
				matrix[i][j].rect = rect;
				window.draw(rect);
			}
		}
	}

}

int Field::collision(Ball &ball, const Paddle &paddle) {

	int col;
		//przypadek, gdy pileczka uderzy w lewy bok okna
		 if (ball.getPosition().x == 0) {
			ball.changeX();
			return 5;
					}
		//przypadek, gdy pileczka uderzy w prawy bok okna
		else if (ball.getPosition().x + 2 * ball.ball.getRadius() == window_width) {
			ball.changeX();
			return 5;
		}
		//przypadek, gdy pileczka uderzy w gore okna
		else if (ball.getPosition().y == 0) {
			ball.changeY();
			return 5;
					}
		//przypadek, gdy pileczka uderzy w paletke
		else if ((ball.getPosition().y + 2 * ball.ball.getRadius() == paddle.paddle.getPosition().y &&
			ball.getPosition().x >= paddle.paddle.getPosition().x &&
			ball.getPosition().x <= paddle.getSize().x + paddle.paddle.getPosition().x) ||
			(ball.getPosition().y + 2 * ball.ball.getRadius() == paddle.paddle.getPosition().y &&
				ball.getPosition().x + 2 * ball.ball.getRadius() >= paddle.paddle.getPosition().x &&
				ball.getPosition().x + 2 * ball.ball.getRadius() <= paddle.getSize().x + paddle.paddle.getPosition().x)) 
		{
			ball.changeY();
			return 6;
		}
		else if (ball.getPosition().y + 2 * ball.ball.getRadius() > paddle.paddle.getPosition().y) {
			return 7;
		}


					//petle i sprawdzanie kazdego bloczka z kazdej strony

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			col = 0;
			if (!matrix[i][j].destroyed) {
					//przypadek, gdy zderzenie z gorna czescia klocka zakladajac gorny lewy rog pilki
					if ((ball.getPosition().x >= matrix[i][j].rect.getPosition().x &&
						ball.getPosition().x <= (matrix[i][j].rect.getPosition().x + matrix[i][j].rect.getSize().x) &&
						ball.getPosition().y + 2 * ball.ball.getRadius() == matrix[i][j].rect.getPosition().y) ||
						//drugi przypadek
						((ball.getPosition().x + 2 * ball.ball.getRadius()) >= matrix[i][j].rect.getPosition().x &&
						(ball.getPosition().x + 2 * ball.ball.getRadius()) <= (matrix[i][j].rect.getPosition().x + matrix[i][j].rect.getSize().x) &&
							ball.getPosition().y + 2 * ball.ball.getRadius() == matrix[i][j].rect.getPosition().y))
					{
						matrix[i][j].hits_to_destroy--;
						if (matrix[i][j].hits_to_destroy == 0)
							matrix[i][j].destroyed = true;
						ball.changeY();
						return 1;
					}
					//przypadek, gdy zderzenie z dolna czescia klocka zakladajac gorny lewy rog pilki
					else if (((ball.getPosition().x >= matrix[i][j].rect.getPosition().x) &&
						(ball.getPosition().x <= (matrix[i][j].rect.getPosition().x + matrix[i][j].rect.getSize().x)) &&
						(ball.getPosition().y == (matrix[i][j].rect.getPosition().y + matrix[i][j].rect.getSize().y))) ||
						//drugi przypadek
						(((ball.getPosition().x + 2 * ball.ball.getRadius()) >= matrix[i][j].rect.getPosition().x) &&
						((ball.getPosition().x + 2 * ball.ball.getRadius()) <= (matrix[i][j].rect.getPosition().x + matrix[i][j].rect.getSize().x)) &&
						(ball.getPosition().y == matrix[i][j].rect.getPosition().y + matrix[i][j].rect.getSize().y)))
					{
						matrix[i][j].hits_to_destroy--;
						if (matrix[i][j].hits_to_destroy == 0)
							matrix[i][j].destroyed = true;
						ball.changeY();
						return 3;
					}
					//przypadek, gdy zderzenie z lewa czesccia klocka zakladajac gorny lewy rog pilki
					else if ((ball.getPosition().y <= (matrix[i][j].rect.getPosition().y + matrix[i][j].rect.getSize().y) &&
						ball.getPosition().y >= matrix[i][j].rect.getPosition().y &&
						ball.getPosition().x + 2 * ball.ball.getRadius() == matrix[i][j].rect.getPosition().x) ||
						//drugi przypadek
						((ball.getPosition().y + 2 * ball.ball.getRadius()) <= (matrix[i][j].rect.getPosition().y + matrix[i][j].rect.getSize().y) &&
						(ball.getPosition().y + 2 * ball.ball.getRadius()) >= matrix[i][j].rect.getPosition().y &&
						ball.getPosition().x + 2 * ball.ball.getRadius() == matrix[i][j].rect.getPosition().x))
					{
						matrix[i][j].hits_to_destroy--;
						if (matrix[i][j].hits_to_destroy == 0)
							matrix[i][j].destroyed = true;
						ball.changeX();
						return 4;
					}
					//przypadek, gdy zderzenie z prawa czescia klocka zakladajac gorny lewy rog pilki
					else if((ball.getPosition().y <= (matrix[i][j].rect.getPosition().y + matrix[i][j].rect.getSize().y) &&
						ball.getPosition().y >= matrix[i][j].rect.getPosition().y &&
						ball.getPosition().x == (matrix[i][j].rect.getPosition().x + matrix[i][j].rect.getSize().x)) ||
						//drugi przypadek
						((ball.getPosition().y + 2 * ball.ball.getRadius()) <= (matrix[i][j].rect.getPosition().y + matrix[i][j].rect.getSize().y) &&
						(ball.getPosition().y + 2 * ball.ball.getRadius()) >= matrix[i][j].rect.getPosition().y &&
							ball.getPosition().x == (matrix[i][j].rect.getPosition().x + matrix[i][j].rect.getSize().x)))
					{
						matrix[i][j].hits_to_destroy--;
						if (matrix[i][j].hits_to_destroy == 0)
							matrix[i][j].destroyed = true;
						ball.changeX();
						return 2;
					}
			}
		}
	}
	return 0;
}


void Field::reset(sf::RenderWindow &window) {
	level = 1;
	columns = 6;
	rows = 5;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (i == 0) {
				matrix[i][j].r = 255;
				matrix[i][j].g = 0;
				matrix[i][j].b = 0;
			}
			else if (i == 1) {
				matrix[i][j].r = 0;
				matrix[i][j].g = 255;
				matrix[i][j].b = 255;
			}
			else if (i == 2) {
				matrix[i][j].r = 0;
				matrix[i][j].g = 0;
				matrix[i][j].b = 235;
			}
			else if (i == 3) {
				matrix[i][j].r = 255;
				matrix[i][j].g = 0;
				matrix[i][j].b = 0;
			}
			else {
				matrix[i][j].r = 0;
				matrix[i][j].g = 225;
				matrix[i][j].b = 0;
			}
			matrix[i][j].hits_to_destroy = 1;
			matrix[i][j].destroyed = false;
		}
	}
	side_padding = 50;
	top_padding = 50;
	int x_size_for_all_blocks = window.getSize().x - side_padding * 2 - ((columns - 1) * 10);
	int y_size_for_all_blocks = (window.getSize().y / 3);
	block_width = x_size_for_all_blocks / columns;
	block_height = y_size_for_all_blocks / rows;
	window_width = window.getSize().x;
}