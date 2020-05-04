#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

#define MAX_NUMBER_OF_ITEMS 4

class Menu
{

public:

	Menu(float width, float height);
	~Menu();
	void draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();

	int getPressedItem() {
		return selectedItem;
	}

private:
	int selectedItem;
	Font font;
	Text menu[MAX_NUMBER_OF_ITEMS];
	Texture texture;

};