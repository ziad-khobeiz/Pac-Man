#include "GameSound.h"

GameSound::GameSound(float width, float height)
{
	font.loadFromFile("assets/font.ttf");

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Yellow);
	menu[0].setString("Turn Off");
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));
	menu[0].setCharacterSize(80);
	menu[0].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2);

	menu[1].setFont(font);
	menu[1].setString("back");
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));
	menu[1].setCharacterSize(80);
	menu[1].setOrigin(menu[1].getLocalBounds().width / 2, menu[1].getLocalBounds().height / 2);

	selectedItem = 0;
}

GameSound::~GameSound()
{
}

void GameSound::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color(0, 0, 30));

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; ++i) {
		window.draw(menu[i]);
	}

}

void GameSound::MoveUp()
{
	if (selectedItem >= 1) {

		menu[selectedItem].setFillColor(sf::Color::White);
		selectedItem--;
		menu[selectedItem].setFillColor(sf::Color::Yellow);

	}
}

void GameSound::MoveDown()
{
	if (selectedItem + 1 < MAX_NUMBER_OF_ITEMS) {

		menu[selectedItem].setFillColor(sf::Color::White);
		selectedItem++;
		menu[selectedItem].setFillColor(sf::Color::Yellow);

	}
}

void GameSound::setString(bool volume_is_on)
{

	menu[0].setString("Turn " + std::string(volume_is_on ?  "Off" : "On"));
	menu[0].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2);

}
