#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Pacman.h"
#define Delete_Key 8
#define Enter_Key 13
#define Escape_Key 27
#define Space_Key 32

struct PlayerData {
	int score;
	float time;
	std::string name;
};

class NameMenu
{
public:

	NameMenu(float width, float height);
	void draw(sf::RenderWindow& window);
	void TypeOn(sf::Event input);
	void addChar(int charTyped);
	void DeleteLastChar();
	void setScore(int new_score);
	void setTime(sf::Time new_time);
	void addToFile();
	std::string getString();

private:

	int fileScore;
	float fileTime;
	sf::Text m_score, m_time;
	sf::Text textbox;
	std::ostringstream text;
	int limit;
	sf::Text message;
	sf::Font font;
};