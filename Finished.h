#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

#define MAX_NUMBER_OF_ITEMS 2

class Finished
{

public:

	Finished(float width, float height);
	~Finished();
	void draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();
	void changeString(std::string newMessage);
	int getPressedItem() {
		return selectedItem;
	}

private:
	int selectedItem;
	Font font;
	Text menu[MAX_NUMBER_OF_ITEMS];
	Text message;
	Texture texture;

};
