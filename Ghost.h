#pragma once

#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animator.h"
#include "Maze.h"
#include "Pacman.h"

class Ghost
{
public:

	Ghost(sf::Texture &texture, int type, Pacman *pacman);

	~Ghost();

	enum Type {
		Blinky, Pinky, Inky, Clyde
	};

	void setSpeed(float newSpeed);
	float getSpeed();
	void draw(sf::RenderWindow &window);
	bool isBlue();
	void makeBlue(sf::Time duration);
	void update(sf::Time delta);
	void setDirection(int direction);
	void setMaze(Maze *current_maze);
	void makeAlive();
	int ShortestPath(sf::Vector2i ghostPosition, sf::Vector2i finalPosition);
	void set_volume(bool);
	sf::Vector2i getInitialPosition();
private:

	float speed;
	bool is_blue, volume_on,is_dying;
	sf::Time blueDuration;
	sf::Time ghostBuffer;
	sf::Sprite ghost;
	Animator smartAnimator[4], dyingAnimator[4];
	Animator blueAnimator;
	Maze *m_maze;
	Pacman *m_pacman;
	sf::Vector2i current_direction, next_direction; 
	sf::Vector2f current_position;
	int ghostType;
	sf::SoundBuffer pacman_death_buffer, pacman_eatghost_buffer;
	sf::Sound pacman_death, pacman_eatghost;
	sf::Clock m_clock;
};

