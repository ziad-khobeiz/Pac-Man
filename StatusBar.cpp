#include "StatusBar.h"
#include <SFML/Graphics.hpp>
#include <iostream>

StatusBar::StatusBar(sf::Texture& texture, Pacman* pacman) : m_pacman(pacman), life(texture)
{

	font.loadFromFile("assets/font.ttf");
	m_score.setFont(font);
	m_score.setCharacterSize(40);
	m_time.setFont(font);
	m_time.setCharacterSize(40);
	life.setTextureRect(sf::IntRect(17 * 45, 2 * 45,45,45));

}

StatusBar::~StatusBar() {


}

void StatusBar::draw(sf::RenderWindow& window) {
	
	for (int i = 0; i < m_pacman->getLives(); ++i) {

		life.setPosition(sf::Vector2f(i * 50, 18 * 50));
		window.draw(life);

	}

	m_score.setString("Score: " + std::to_string(m_pacman->getScore()));
	m_score.setOrigin(m_score.getGlobalBounds().width / 2, m_score.getGlobalBounds().height / 2);
	m_score.setPosition(18 * 50 / 2, 18.15 * 50);
	window.draw(m_score);

	std::string timeSeconds = std::to_string(int(m_pacman->getTime().asSeconds()) % 60);
	if (timeSeconds.size() < 2) timeSeconds = '0' + timeSeconds;

	std::string timeMinutes = std::to_string(int(m_pacman->getTime().asSeconds() / 60));
	if (timeMinutes.size() < 2) timeMinutes = '0' + timeMinutes;

	m_time.setString(timeMinutes + ':' + timeSeconds);
	m_time.setOrigin(m_time.getGlobalBounds().width, m_score.getGlobalBounds().height / 2);
	m_time.setPosition(17.5 * 50, 18.15 * 50);
	window.draw(m_time);

}