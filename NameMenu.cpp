#include "NameMenu.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;


bool comp(PlayerData a, PlayerData b)
{
	if (a.score == b.score)
		return a.time < b.time;
	return a.score > b.score;
}
NameMenu::NameMenu(float width, float height)
{
	font.loadFromFile("assets/font.ttf");

	m_score.setFont(font);
	m_score.setCharacterSize(40);
	m_score.setPosition(sf::Vector2f(width / 2, height / 2 - (75 + 75/2.0)));

	m_time.setFont(font);
	m_time.setCharacterSize(40);
	m_time.setPosition(sf::Vector2f(width / 2, height / 2 - 75/2.0));

	textbox.setFont(font);
	textbox.setFillColor(sf::Color::Red);
	textbox.setPosition(sf::Vector2f(width / 2, height / 2 + 75/2.0));
	textbox.setCharacterSize(30);
	textbox.setString("Enter your name: _");
	textbox.setOrigin(textbox.getLocalBounds().width / 2, textbox.getLocalBounds().height / 2);

	message.setFont(font);
	message.setString("Press Enter to proceed");
	message.setPosition(sf::Vector2f(width / 2, height / 2 + 75 + 75/2.0));
	message.setCharacterSize(30);
	message.setOrigin(message.getLocalBounds().width / 2, message.getLocalBounds().height / 2);

	limit = 20;
}

void NameMenu::TypeOn(sf::Event input)
{
		int charTyped = input.text.unicode;
		if (charTyped < 128)
		{
			if (text.str().length() <= limit)
				addChar(charTyped);
			else if (text.str().length() > limit && charTyped == Delete_Key)
				DeleteLastChar();
		}
}

void NameMenu::addChar(int charTyped)
{
	if (charTyped != Delete_Key && charTyped != Escape_Key && charTyped != Enter_Key && charTyped != Space_Key)
	{
		text << char(charTyped);
	}
	else if (charTyped == Delete_Key)
	{
		if (text.str().size() > 0)
		{
			DeleteLastChar();
		}
	}
	textbox.setString("Enter your name: " + text.str() + "_");
	textbox.setOrigin(textbox.getLocalBounds().width / 2, textbox.getLocalBounds().height / 2);
}

void NameMenu::DeleteLastChar()
{
	std::string modifiedString = text.str();
	if (!modifiedString.empty())
		modifiedString.pop_back();
	text.str("");
	text << modifiedString;
	textbox.setString("Enter your name: " + text.str());
	textbox.setOrigin(textbox.getLocalBounds().width / 2, textbox.getLocalBounds().height / 2);
}

void NameMenu::setScore(int new_score)
{
	m_score.setString("Your Score: " + std::to_string(new_score));
	m_score.setOrigin(m_score.getGlobalBounds().width / 2, m_score.getGlobalBounds().height / 2);
	fileScore = new_score;

}

void NameMenu::setTime(sf::Time new_time)
{
	std::string timeSeconds = std::to_string(int(new_time.asSeconds()) % 60);
	if (timeSeconds.size() < 2) timeSeconds = '0' + timeSeconds;

	std::string timeMinutes = std::to_string(int(new_time.asSeconds()) / 60);
	if (timeMinutes.size() < 2) timeMinutes = '0' + timeMinutes;

	m_time.setString("Time: " + timeMinutes + ':' + timeSeconds);
	m_time.setOrigin(m_time.getGlobalBounds().width / 2, m_time.getGlobalBounds().height / 2);
	fileTime = new_time.asSeconds();

}

void NameMenu::addToFile()
{
	vector <PlayerData> playersData;

	ifstream readFromFile;
	readFromFile.open("assets/Scoreboard.txt");

	while (!readFromFile.eof()) {

		PlayerData player;
		readFromFile >> player.name;
		if (player.name.empty()) continue;
		readFromFile >> player.score;
		readFromFile >> player.time;
		playersData.push_back(player);
	}

	readFromFile.close();

	playersData.push_back({fileScore, fileTime, text.str()});
	sort(playersData.begin(), playersData.end(),comp);

	ofstream writeToFile;
	writeToFile.open("assets/Scoreboard.txt");

	for (int i = 0; i < min(10,int(playersData.size())); ++i) {

		writeToFile << playersData[i].name;
		writeToFile << ' ';
		writeToFile << playersData[i].score;
		writeToFile << ' ';
		writeToFile << playersData[i].time;
		writeToFile << '\n';
	}
	writeToFile.close();
	text.str("");
	textbox.setString("Enter your name: _");
	textbox.setOrigin(textbox.getLocalBounds().width / 2, textbox.getLocalBounds().height / 2);
}

std::string NameMenu::getString()
{
	return text.str();
}

void NameMenu::draw(sf::RenderWindow & window)
{
	window.draw(textbox);
	window.draw(message);
	window.draw(m_score);
	window.draw(m_time);
}