#include "Dot.h"

sf::CircleShape getDot()
{
	sf::CircleShape dot;
	dot.setFillColor(sf::Color::White);
	dot.setRadius(4);
	dot.setOrigin(4, 4);
	return dot;
}

sf::CircleShape getSuperdot()
{
	sf::CircleShape superdot;
	superdot.setFillColor(sf::Color(250, 184, 152));
	superdot.setRadius(8);
	superdot.setOrigin(8, 8);
	return superdot;
}
