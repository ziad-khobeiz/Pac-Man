#pragma once
#include<SFML\Graphics.hpp> 

class Bonus 
{

public:

	Bonus(sf::Texture& texture);
	~Bonus();

	void drawBonus(sf::RenderWindow& window, float x, float y);

private:
	sf::Sprite fruit;

};
