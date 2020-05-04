#include "Ready.h"
#include <iostream>
#include <cmath>

Ready::Ready(float width, float height)
{

	font.loadFromFile("assets/font.ttf");

	message.setFont(font);
	message.setString("Get Ready!");
	message.setPosition(sf::Vector2f(width / 2, height / 2 - 75));
	message.setCharacterSize(110);
	message.setOrigin(message.getLocalBounds().width / 2, message.getLocalBounds().height / 2);
	time = sf::seconds(3);
	remainingTime.setFont(font);
	remainingTime.setString(char('0'+int(time.asSeconds())));
	remainingTime.setPosition(sf::Vector2f(width / 2, height / 2 + 75));
	remainingTime.setCharacterSize(110);
	remainingTime.setOrigin(remainingTime.getLocalBounds().width / 2, remainingTime.getLocalBounds().height / 2);

}

void Ready::draw(sf::RenderWindow& window)
{

	window.clear(sf::Color(0, 0, 30));
	window.draw(message);
	window.draw(remainingTime);


}

bool Ready::update(sf::Time deltaTime) {

	time -= deltaTime;
	remainingTime.setString(char('1' + int(time.asSeconds())));

	if (time <= sf::seconds(0)) {

		time = sf::seconds(3);
		return true;

	}

	return false;

}

Ready::~Ready()
{
}
