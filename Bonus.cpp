#include "Bonus.h"

Bonus::Bonus(sf::Texture& texture) : fruit(texture)
{
	fruit.setOrigin(22.5, 22.5);
	fruit.setTextureRect(sf::IntRect(12 * 45, 0, 45, 45));
}

void Bonus::drawBonus(sf::RenderWindow& window, float x, float y)
{
	fruit.setPosition(x, y);
	window.draw(fruit);
}

Bonus::~Bonus()
{
}