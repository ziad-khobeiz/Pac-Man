#include "Finished.h"

Finished::Finished(float width, float height)
{

	font.loadFromFile("assets/font.ttf");

	message.setFont(font);
	message.setFillColor(Color::White);
	message.setPosition(Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 2) * 1));
	message.setCharacterSize(120);

	menu[0].setFont(font);
	menu[0].setFillColor(Color::Yellow);
	menu[0].setString("Scoreboard");
	menu[0].setPosition(Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 2) * 2));
	menu[0].setCharacterSize(80);
	menu[0].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2);

	menu[1].setFont(font);
	menu[1].setString("Main Menu");
	menu[1].setPosition(Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 2) * 3));
	menu[1].setCharacterSize(80);
	menu[1].setOrigin(menu[1].getLocalBounds().width / 2, menu[1].getLocalBounds().height / 2);

	
	selectedItem = 0;

}

void Finished::draw(RenderWindow& window)
{

	window.clear(Color(0, 0, 30));

	window.draw(message);

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; ++i) {
		window.draw(menu[i]);
	}

}

void Finished::MoveUp()
{

	if (selectedItem >= 1) {

		menu[selectedItem].setFillColor(Color::White);
		selectedItem--;
		menu[selectedItem].setFillColor(Color::Yellow);

	}

}

void Finished::MoveDown()
{

	if (selectedItem + 1 < MAX_NUMBER_OF_ITEMS) {

		menu[selectedItem].setFillColor(Color::White);
		selectedItem++;
		menu[selectedItem].setFillColor(Color::Yellow);

	}

}

Finished::~Finished()
{
}

void Finished::changeString(std::string newMessage) {

	message.setString(newMessage);
	message.setOrigin(message.getLocalBounds().width / 2, message.getLocalBounds().height / 2);
}