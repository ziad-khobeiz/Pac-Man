#pragma once
#include <SFML/Graphics.hpp>

class Ready
{

public:

	Ready(float width, float height);
	~Ready();
	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	bool update(sf::Time deltaTime);

private:
	sf::Font font;
	sf::Texture texture;
	sf::Text message;
	sf::Text remainingTime;
	sf::Time time;
};
