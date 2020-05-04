#include "Pacman.h"
#include <SFML\Graphics.hpp>
#include <iomanip>
#include <iostream>

using namespace std;

sf::Vector2i directions[] = { sf::Vector2i(1, 0), sf::Vector2i(0, 1), sf::Vector2i(-1, 0), sf::Vector2i(0, -1) };

Pacman::Pacman(sf::Texture& texture) : speed(200), pac_vision(texture), pac_is_dying(0), pac_is_dead(0), current_direction(0,0), lives(3), score(0), playTime(sf::Time::Zero) {

	pac_vision.setOrigin(22.5, 22.5);
	
	dyingAnimator.addFrame(sf::IntRect(765, 0,45,45));
	
	for (int i = 0; i < 11; ++i)
		dyingAnimator.addFrame(sf::IntRect(315, 45 * i, 45, 45));

	for (int i = 0; i < 3; ++i)
		runningAnimator.addFrame(sf::IntRect(17 * 45, 45 * i, 45, 45));

	runningAnimator.setAnimation(sf::seconds(0.2), true);

}

Pacman::~Pacman() {}

void Pacman::setSpeed(float newSpeed) {

	speed = newSpeed;

}

float Pacman::getSpeed() {

	return speed;

}

void Pacman::update(sf::Time delta) {

	// updating the animation of pacman
	
	if (pac_is_dying) {

		dyingAnimator.update(delta);
		dyingAnimator.animate(pac_vision);

		if (!dyingAnimator.isPlaying()) {

			lives--;
			setMaze(m_maze);
			if (!lives) pac_is_dead = 1;
			pac_is_dying = 0;

		}

	}
	else if(!pac_is_dead) {

		runningAnimator.update(delta);
		runningAnimator.animate(pac_vision);

	}

	// updating the motion of pacman

	if (!pac_is_dead && !pac_is_dying) {

		playTime += delta;

		float pixel_displacement = delta.asSeconds() * speed;

		sf::Vector2f next_position, offset, centerOfCell;

		next_position = current_position + sf::Vector2f(current_direction) * pixel_displacement;

		sf::Vector2i cell_position = m_maze->pixelToCell(current_position);

		centerOfCell = m_maze->cellToPixel(cell_position);

		int CellSize = m_maze->getCellSize();

		offset.x = fmod(current_position.x, CellSize) - CellSize / 2;
		offset.y = fmod(current_position.y, CellSize) - CellSize / 2;

		// eating dots

		if (fabs(offset.x) <= (CellSize - 45) / 2.0 && fabs(offset.y) <= (CellSize - 45) / 2.0)
			score += 10 * m_maze->removeDot(cell_position), score += 50*m_maze->removeSuperDot(cell_position), score += 100 * m_maze->removeBonus(cell_position);

		if (current_direction != next_direction && !m_maze->isWall(cell_position + next_direction) &&
			((fabs(offset.x) <= (CellSize - 45) / 2.0 && fabs(offset.y) <= (CellSize - 45) / 2.0) || current_direction.x == next_direction.x || current_direction.y == next_direction.y)) {

			// makes the current position exactly in the middle of the cell i.e. offset = zero

			if (!(current_direction.x == next_direction.x || current_direction.y == next_direction.y))
				current_position = m_maze->cellToPixel(cell_position);

			current_direction = next_direction;

			for (int i = 0; i < 4; ++i)
				if (current_direction == directions[i])
					pac_vision.setRotation(i * 90);

		}
		else if (m_maze->isWall(cell_position + current_direction)
			&& (fabs(current_position.x - centerOfCell.x) + fabs(current_position.y - centerOfCell.y) <= fabs(current_position.x - next_position.x) + fabs(current_position.y - next_position.y))) {

			current_position = centerOfCell;

		}
		else current_position = next_position;

	}

}

void Pacman::makeDie() {

	if (!pac_is_dying && !pac_is_dead) {

		pac_is_dying = 1;
		dyingAnimator.setAnimation(sf::seconds(1.5343), false);

	}

}

bool Pacman::isDying() {
	return pac_is_dying;
}

bool Pacman::isDead() {
	return pac_is_dead;
}

void Pacman::draw(sf::RenderWindow &window) {

	if (pac_is_dead) return;

	pac_vision.setPosition(current_position);

	window.draw(pac_vision);
	
	/*sf::CircleShape rect;
	rect.setRadius(17);
	rect.setOrigin(17,17);
	rect.setFillColor(sf::Color::Red);
	rect.setPosition(pac_vision.getPosition());
	window.draw(rect);*/

}

void Pacman::setPosition(float x, float y) {

	current_position = sf::Vector2f(x, y);

}


sf::Vector2f Pacman::getPosition() {

	return current_position;

}

void Pacman::setDirection(sf::Vector2i direction) {

	next_direction = direction;

}

sf::Vector2i Pacman::getDirection() {

	return current_direction;

}

void Pacman::setMaze(Maze* current_maze) {

	pac_is_dead = 0;
	m_maze = current_maze;
	current_position = m_maze->cellToPixel(m_maze->getPacmanPosition());
	next_direction = current_direction = sf::Vector2i(0, 0);

}

void Pacman::reset() {

	lives = 3;
	score = 0;
	playTime = sf::Time::Zero;

}

int Pacman::getLives() {

	return lives;

}
int Pacman::getScore() {

	return score;

}

sf::Time Pacman::getTime() {

	return playTime;

}