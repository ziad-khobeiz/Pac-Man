#include <SFML/Graphics.hpp>
#include "Pacman.h"

#pragma once
class StatusBar
{

public:

	StatusBar(sf::Texture& texture, Pacman *pacman);

	~StatusBar();

	void draw(sf::RenderWindow& window);


private:

	Pacman *m_pacman;
	sf::Sprite life;
	sf::Text m_score, m_time;
	sf::Font font;

};