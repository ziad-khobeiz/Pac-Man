#include "Scoreboard.h"
#include <fstream>

Scoreboard::Scoreboard(float width, float height)
{
	font.loadFromFile("assets/font.ttf");

	m_name.setFont(font);
	m_time.setFont(font);
	m_score.setFont(font);
	
	title.setFillColor(sf::Color::Red);
	//m_time.setFillColor(sf::Color::Red);
	//m_score.setFillColor(sf::Color::Red);
	
	note.setFont(font);
	note.setString("Press ESC to return back");
	note.setCharacterSize(30);
	note.setFillColor(sf::Color::Yellow);
	note.setPosition(sf::Vector2f(width / 2, 85));
	note.setOrigin(note.getLocalBounds().width / 2, note.getLocalBounds().height / 2);

	title.setFont(font);
	title.setString("Scoreboard");
	title.setPosition(sf::Vector2f(width / 2, 10));
	title.setCharacterSize(70);
	title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);

}

void Scoreboard::draw(sf::RenderWindow & window)
{
	window.clear(sf::Color(0, 0, 30));
	window.draw(title);
	window.draw(note);
	float counter = 4.5;
	int rank = 1;
	std::ifstream readFromFile;
	readFromFile.open("assets/Scoreboard.txt");
	m_name.setString("Name:");
	m_score.setString("Score:");
	m_time.setString("Time:");
	
	m_name.setPosition({ 1.8 * 50, 50 * (counter - float(1.5)) });
	m_score.setPosition({ 10.8 * 50,50 * (counter - float(1.5)) });
	m_time.setPosition({ 14.8 * 50,50 * (counter - float(1.5)) });
	m_score.setOrigin(m_score.getLocalBounds().width / 2, 0);
	window.draw(m_name);
	window.draw(m_score);
	window.draw(m_time);

	while (!readFromFile.eof()) {

		PlayerData player;
		readFromFile >> player.name;
		if (player.name.empty()) continue;
		m_name.setString(std::to_string(rank) + " - " + player.name);
		readFromFile >> player.score;
		m_score.setString(std::to_string(player.score));
		readFromFile >> player.time;
		std::string timeSeconds = std::to_string(int(player.time) % 60);
		if (timeSeconds.size() < 2) timeSeconds = '0' + timeSeconds;

		std::string timeMinutes = std::to_string(int(player.time) / 60);
		if (timeMinutes.size() < 2) timeMinutes = '0' + timeMinutes;
		m_time.setString(timeMinutes + ':' + timeSeconds);

		m_name.setPosition({ 1.8 * 50, 50 * counter });
		m_score.setPosition({ 10.8 * 50,50 * counter });
		m_time.setPosition({ 14.8 * 50,50 * counter });
		m_score.setOrigin(m_score.getLocalBounds().width / 2, 0);
		window.draw(m_name);
		window.draw(m_score);
		window.draw(m_time);
		counter += 1.5;
		++rank;
	}


	readFromFile.close();
}