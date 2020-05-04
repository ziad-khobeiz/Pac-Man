#include "SingleMenu.h"

SingleMenu::SingleMenu(float width, float height)
{

	font.loadFromFile("assets/font.ttf");

	menu[0].setFont(font);
	menu[0].setFillColor(Color::Yellow);
	menu[0].setString("Play");
	menu[0].setPosition(Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));
	menu[0].setCharacterSize(80);
	menu[0].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2);

	menu[1].setFont(font);
	menu[1].setString("Scoreboard");
	menu[1].setPosition(Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));
	menu[1].setCharacterSize(80);
	menu[1].setOrigin(menu[1].getLocalBounds().width / 2, menu[1].getLocalBounds().height / 2);

	menu[2].setFont(font);
	menu[2].setString("Back");
	menu[2].setPosition(Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));
	menu[2].setCharacterSize(80);
	menu[2].setOrigin(menu[2].getLocalBounds().width / 2, menu[2].getLocalBounds().height / 2);

	selectedItem = 0;

}

void SingleMenu::draw(RenderWindow& window)
{

	window.clear(Color(0, 0, 30));

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; ++i) {
		window.draw(menu[i]);
	}

}

void SingleMenu::MoveUp()
{

	if (selectedItem >= 1) {

		menu[selectedItem].setFillColor(Color::White);
		selectedItem--;
		menu[selectedItem].setFillColor(Color::Yellow);

	}

}

void SingleMenu::MoveDown()
{

	if (selectedItem + 1 < MAX_NUMBER_OF_ITEMS) {

		menu[selectedItem].setFillColor(Color::White);
		selectedItem++;
		menu[selectedItem].setFillColor(Color::Yellow);

	}

}

SingleMenu::~SingleMenu()
{
}
