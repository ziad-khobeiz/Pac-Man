#pragma once
#include <SFML/Graphics.hpp>

#define MAX_NUMBER_OF_ITEMS 2

class GameSound
{
public:

	GameSound(float width, float height);
	~GameSound();
	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	void setString(bool volume_is_on);

	int getPressedItem() {
		return selectedItem;
	}

private:
	int selectedItem;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::Texture texture;
};

