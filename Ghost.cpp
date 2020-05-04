#include "Ghost.h"
#include <cstring>
#include <queue>

#define maxPositions 30

sf::Vector2i ghostDirections[] = { sf::Vector2i(1, 0), sf::Vector2i(0, 1), sf::Vector2i(-1, 0), sf::Vector2i(0, -1) };

Ghost::Ghost(sf::Texture& texture, int type, Pacman* pacman) : speed(150), is_blue(0), blueDuration(sf::Time::Zero), ghost(texture), ghostType(type), ghostBuffer(sf::Time::Zero), current_direction(0, -1), next_direction(0, -1), m_pacman(pacman)
{

	ghost.setOrigin(22.5, 22.5);

	blueAnimator.addFrame(sf::IntRect(0, 11 * 45, 45, 45));
	blueAnimator.addFrame(sf::IntRect(0, 12 * 45, 45, 45));
	blueAnimator.setAnimation(sf::seconds(2), true);

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 2; ++j) 
		{
			smartAnimator[i].addFrame(sf::IntRect(type * 45, (2 * i + j) * 45, 45, 45));
			smartAnimator[i].setAnimation(sf::seconds(0.2), true);
		}
	}
	for (int i = 0; i < 4; ++i) 
	{
			dyingAnimator[(4-i)%4].addFrame(sf::IntRect(6*45,(5+i)*45,45,45));
			dyingAnimator[(4-i)%4].setAnimation(sf::seconds(0.2),true);
	}
	
	pacman_death_buffer.loadFromFile("assets/pacman_death.wav");
	pacman_death.setBuffer(pacman_death_buffer);

	pacman_eatghost_buffer.loadFromFile("assets/pacman_eatghost.wav");
	pacman_eatghost.setBuffer(pacman_eatghost_buffer);

	volume_on = true;
	is_dying = false; 
}


Ghost::~Ghost()
{
}
sf::Vector2i Ghost::getInitialPosition()
{
	if (ghostType == Inky)
		return m_maze->getInkyPosition();
	else if (ghostType == Blinky)
		return m_maze->getBlinkyPosition();
	else if (ghostType == Pinky)
		return m_maze->getPinkyPosition();
	else 
		return m_maze->getClydePosition();
}
void Ghost::setSpeed(float newSpeed) {

	speed = newSpeed;

}

float Ghost::getSpeed() {

	return speed;

}

bool Ghost::isBlue() {

	return is_blue;

}

void Ghost::makeBlue(sf::Time duration)
{
	is_blue = 1;
	ghostBuffer = sf::Time::Zero;
	blueDuration = duration;
}


void Ghost::update(sf::Time delta) {

	// updating the animation

	if (is_blue) {

		ghostBuffer += delta;

		if (ghostBuffer >= blueDuration) {

			is_blue = 0;
			ghostBuffer = sf::Time::Zero;

		}

	}

	 if (is_dying)
	{
		for (int i = 0; i < 4; ++i) 
		{
			if (current_direction == ghostDirections[i]) 
			{

				dyingAnimator[i].update(delta);
				dyingAnimator[i].animate(ghost);

			}
		}
	}
    else if (is_blue) {

		blueAnimator.update(delta);
		blueAnimator.animate(ghost);

	}
	else {

		if (current_direction == sf::Vector2i(0, 0)) {

			smartAnimator[0].update(delta);
			smartAnimator[0].animate(ghost);

		}
		else {

			for (int i = 0; i < 4; ++i) {

				if (current_direction == ghostDirections[i]) {

					smartAnimator[i].update(delta);
					smartAnimator[i].animate(ghost);

				}

			}

		}
	}

	// Using artificial intelligence algorithms
	// to change the ghosts direction to the optimal direction to run towards to/away from Pacman based on the state of the ghost

	if (is_blue) {

		sf::Vector2i cell_position = m_maze->pixelToCell(current_position);
		int maxPath = 0;
		sf::Vector2i maxDirection;

		for (int i = 0; i < 4; ++i) {

			if (!m_maze->isValid(cell_position + ghostDirections[i])) continue;

			int currentPath = ShortestPath(cell_position + ghostDirections[i], m_maze->pixelToCell(m_pacman->getPosition()));

			if (currentPath > maxPath) {

				maxPath = currentPath;
				maxDirection = ghostDirections[i];

			}

		}

		next_direction = maxDirection;

	}
	else if (is_dying)
	{
		sf::Vector2i cell_position = m_maze->pixelToCell(current_position);
		int minPath = INT_MAX;
		sf::Vector2i minDirection, initial_cell;
		initial_cell = getInitialPosition();

		for (int i = 0; i < 4; ++i) 
		{

			if (!m_maze->isValid(cell_position + ghostDirections[i])) 
				continue;
			int currentPath = ShortestPath(cell_position + ghostDirections[i], initial_cell);
			if (currentPath < minPath) 
			{
				minPath = currentPath;
				minDirection = ghostDirections[i];
			}
		}
		next_direction = minDirection;
	}
	else {


		sf::Vector2i finalCell = m_maze->pixelToCell(m_pacman->getPosition());

		if (ghostType != Type::Clyde) {

			sf::Vector2i newDirection = ghostDirections[ghostType];

			for (int i = 0; i < 6; ++i) {

				sf::Vector2i newPacmanPosition = m_maze->pixelToCell(m_pacman->getPosition()) + i * newDirection;

				if (m_maze->isValid(newPacmanPosition)) finalCell = newPacmanPosition;

			}

		}

		sf::Vector2i cell_position = m_maze->pixelToCell(current_position);
		int minPath = ShortestPath(cell_position, finalCell) - 1;
		sf::Vector2i minDirection = sf::Vector2i(0, 0);

		for (int i = 0; i < 4; ++i) {


			if (!m_maze->isValid(cell_position + ghostDirections[i])) continue;

			int currentPath = ShortestPath(cell_position + ghostDirections[i], finalCell) - 1;

			if (currentPath < minPath) {

				minPath = currentPath;
				minDirection = ghostDirections[i];

			}

		}

		next_direction = minDirection;

	}

	// updating the motion

	if (!m_pacman->isDead() && !m_pacman->isDying()) {

		float pixel_displacement = delta.asSeconds() * speed;

		sf::Vector2f next_position, offset, centerOfCell;

		next_position = current_position + sf::Vector2f(current_direction) * pixel_displacement;

		sf::Vector2i cell_position = m_maze->pixelToCell(current_position);

		centerOfCell = m_maze->cellToPixel(cell_position);

		int CellSize = m_maze->getCellSize();

		offset.x = fmod(current_position.x, CellSize) - CellSize / 2;
		offset.y = fmod(current_position.y, CellSize) - CellSize / 2;

		if (current_direction != next_direction && !m_maze->isWall(cell_position + next_direction) &&
			fabs(offset.x) <= (CellSize - 45) / 2.0 && fabs(offset.y) <= (CellSize - 45) / 2.0) {

			current_direction = next_direction;

			// makes the current position exactly in the middle of the cell i.e. offset = zero

			current_position = m_maze->cellToPixel(cell_position);

		}
		else if (m_maze->isWall(cell_position + current_direction)
			&& (fabs(current_position.x - centerOfCell.x) + fabs(current_position.y - centerOfCell.y) <= fabs(current_position.x - next_position.x) + fabs(current_position.y - next_position.y))) {
			//	just for assurance now that the ghost won't collide with a wall, we can delete it later if not needed
			current_position = centerOfCell;

		}
		else current_position = next_position;

		//to stop dying animation
		if (is_dying && fabs(current_position.x - m_maze->cellToPixel(getInitialPosition()).x) <= (CellSize - 45) / 2.0
			&& fabs(current_position.y - m_maze->cellToPixel(getInitialPosition()).y) <= (CellSize - 45) / 2.0)
		{
			is_dying = 0; 
			speed = 100;
			setMaze(m_maze);
		}

		sf::Vector2f pacPosition = m_pacman->getPosition();

		float diffX = pacPosition.x - current_position.x;
		float diffY = pacPosition.y - current_position.y;
		
		if (diffX * diffX + diffY * diffY <= 20 * 20) {

			if (is_blue)
			{
				// return the ghost to it's original state and add x points to the score.
				if (volume_on)
				{
					pacman_eatghost.setVolume(20);
					pacman_eatghost.play();
				}
				makeAlive();
				speed = 200;
				is_dying = true; 

			}
			else if (!is_dying)
			{
				if (volume_on)
				{
					pacman_death.setVolume(20);
					pacman_death.play();
				}
				m_pacman->makeDie();
			}
		}
	}
}

void Ghost::draw(sf::RenderWindow& window) {

	ghost.setPosition(current_position);

	if (!m_pacman->isDead() && !m_pacman->isDying()) window.draw(ghost);

}

void Ghost::setMaze(Maze* current_maze) {

	m_maze = current_maze;
	current_direction = next_direction = { 0,-1 };
	current_position = m_maze->cellToPixel(getInitialPosition());

}

void Ghost::makeAlive()
{
	is_blue = false;
	ghostBuffer = sf::Time::Zero;
}

int Ghost::ShortestPath(sf::Vector2i startPosition, sf::Vector2i finalPosition)
{
	bool visitedPositions[maxPositions][maxPositions];
	std::memset(visitedPositions, false, sizeof visitedPositions);

	std::queue<sf::Vector2i> m_queue;
	m_queue.push(startPosition);
	int steps = 1;
	visitedPositions[startPosition.x][startPosition.y] = true;

	while (!m_queue.empty())
	{

		int queueSize = m_queue.size();

		while (queueSize--)
		{

			if (m_queue.front() == finalPosition) return steps;

			for (int i = 0; i < 4; i++)
			{
				sf::Vector2i newPosition = m_queue.front() + ghostDirections[i];

				if (!m_maze->isWall(newPosition) && !visitedPositions[newPosition.x][newPosition.y])
				{
					m_queue.push(newPosition);
					visitedPositions[newPosition.x][newPosition.y] = true;
				}

			}

			m_queue.pop();

		}

		++steps;

	}

}

void Ghost::set_volume(bool m_volume)
{
	volume_on = m_volume;
}

void Ghost::setDirection(int direction) {

	next_direction = ghostDirections[direction];

}