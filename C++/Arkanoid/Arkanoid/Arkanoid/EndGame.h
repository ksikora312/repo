#ifndef ENDGAME_H
#define ENDGAME_H
#include "SFML\Graphics.hpp"

class EndGame
{
	sf::Text text;
	sf::Text next;
	sf::Font font;
public:
	EndGame();
	~EndGame();
	bool drawMenu(sf::RenderWindow &window);
};



#endif