#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
class Animator
{
public:
	Animator();

	~Animator();

	void addFrame(sf::IntRect picture);
	bool isPlaying();
	void setAnimation(sf::Time animationDuration, bool loop);
	void update(sf::Time delta);
	void animate(sf::Sprite &sprite);

private:
	bool playing, repeat;
	sf::Time duration;
	std::vector<sf::IntRect> frames;
	int curFrame;
	sf::Time timeBuffer;
};

