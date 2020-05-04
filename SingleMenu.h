#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

#define MAX_NUMBER_OF_ITEMS 3

class SingleMenu
{

public:

	SingleMenu(float width, float height);
	~SingleMenu();
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
