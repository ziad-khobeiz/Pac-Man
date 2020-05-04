#pragma once
#include <sfml/Graphics.hpp>
#include "NameMenu.h"
class Scoreboard
{
public:
	Scoreboard(float width, float height);
	void draw(sf::RenderWindow &window);

private:
	sf::Font font;
	sf::Text title, m_score, m_time, m_name, note;
};


