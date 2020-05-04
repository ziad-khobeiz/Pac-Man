#pragma once
#include<SFML\Graphics.hpp>
#include "Animator.h"
#include "Maze.h"

class Pacman {

public:

	Pacman(sf::Texture& texture);

	~Pacman();
	
	void setSpeed(float newSpeed);
	float getSpeed();
	void makeDie();
	bool isDying();
	bool isDead();
	void update(sf::Time delta);
	void draw(sf::RenderWindow &window);
	void setPosition(float x, float y);
	void setDirection(sf::Vector2i direction);
	sf::Vector2f getPosition();
	sf::Vector2i getDirection();
	void setMaze(Maze *current_maze);
	void reset();
	int getLives();
	int getScore();
	sf::Time getTime();

private:

	bool pac_is_dying;
	bool pac_is_dead;
	float speed;
	sf::Sprite pac_vision;
	Maze *m_maze;
	sf::Vector2i current_direction, next_direction; 
	sf::Vector2f current_position;
	Animator runningAnimator;
	Animator dyingAnimator;
	int lives, score;
	sf::Time playTime;

};

