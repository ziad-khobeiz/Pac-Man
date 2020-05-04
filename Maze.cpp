#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "Bonus.h"
#include "Maze.h"
#include "Dot.h"
#include <iostream>

#define CELL_SIZE 50

sf::Vector2i neighbor_direction[] = { sf::Vector2i(1, 0), sf::Vector2i(0, -1), sf::Vector2i(-1, 0), sf::Vector2i(0, 1)};
sf::Vector2i corner_direction[] = { sf::Vector2i(1, -1), sf::Vector2i(-1, -1), sf::Vector2i(-1, 1), sf::Vector2i(1, 1)};
float current_angle[] = { 0, 270, 180, 90 };

Maze::Maze()
	: mazeSize(0, 0)
{
	is_blue = false;
	wallPicture.loadFromFile("assets/wall.png");
	wallPicture.setSmooth(true);
	sheet.loadFromFile("assets/sheet.png");
	sheet.setSmooth(true);
	bound.setTexture(wallPicture);
	outer_bound.setTexture(wallPicture);
	inner_bound.setTexture(wallPicture);
	bound.setTextureRect(sf::IntRect(CELL_SIZE/2, 0, CELL_SIZE/2, CELL_SIZE));
	inner_bound.setTextureRect(sf::IntRect(0, 0, CELL_SIZE / 2, CELL_SIZE / 2));
	outer_bound.setTextureRect(sf::IntRect(0, CELL_SIZE / 2, CELL_SIZE / 2, CELL_SIZE / 2));
	bound.setOrigin(0, CELL_SIZE / 2);
	inner_bound.setOrigin(0, CELL_SIZE / 2);
	outer_bound.setOrigin(0, CELL_SIZE / 2);
	pacman_chomp_buffer.loadFromFile("assets/pacman_chomp.wav");
	pacman_chomp.setBuffer(pacman_chomp_buffer);
	pacman_eatfruit_buffer.loadFromFile("assets/pacman_eatfruit.wav");
	pacman_eatfruit.setBuffer(pacman_eatfruit_buffer);
	m_Dot = getDot();
	m_SuperDot = getSuperdot();
	volume_on = true;
}

bool Maze::isWall(sf::Vector2i position) {

	if (position.x < 0 || position.y < 0 || position.x >= mazeSize.x || position.y >= mazeSize.y) return false;

	return (mazeData[positionToIndex(position)] == CellData::Wall);

}

bool Maze::isValid(sf::Vector2i position) {

	if (position.x < 0 || position.y < 0 || position.x >= mazeSize.x || position.y >= mazeSize.y) return false;

	return (mazeData[positionToIndex(position)] != CellData::Wall);

}

void Maze::set_volume(bool m_volume)
{
	volume_on = m_volume;
}


bool Maze::removeBonus(sf::Vector2i cell)
{
	if (mazeData[positionToIndex(cell)] == CellData::Bonus)
	{
		if (volume_on)
		{
			pacman_eatfruit.setVolume(20);
			pacman_eatfruit.play();
		}
		mazeData[positionToIndex(cell)] = CellData::Empty;
		return true;
	}

	return false;

}


bool Maze::removeDot(sf::Vector2i cell) 
{
	if (mazeData[positionToIndex(cell)] == CellData::Dot) 
	{
		if (volume_on)
		{
			pacman_chomp.setVolume(20);
			pacman_chomp.play();
		}
		--dots, mazeData[positionToIndex(cell)] = CellData::Empty;
		return true;
	}

	return false;

}

bool Maze::removeSuperDot(sf::Vector2i cell) {

	if (mazeData[positionToIndex(cell)] == CellData::SuperDot) 
	{
		if (volume_on)
		{
			pacman_eatfruit.setVolume(20);
			pacman_eatfruit.play();
		}
		dots--;
		mazeData[positionToIndex(cell)] = CellData::Empty;
		is_blue = true;
		return true;
	}

	return false;

}

void Maze::loadLevel(std::string file)
{
	mazeData.clear();
	dots = 0;
	sf::Image levelData;
	levelData.loadFromFile("assets/" + file + ".png");

	mazeSize = sf::Vector2i(levelData.getSize());

	for (unsigned int y = 0; y < mazeSize.y; y++)
	{ 
		for (unsigned int x = 0; x < mazeSize.x; x++)
		{
			sf::Color currentPixel = levelData.getPixel(x, y);

			if (currentPixel == sf::Color::Black)
				mazeData.push_back(CellData::Wall);
			else if (currentPixel == sf::Color::White)
				mazeData.push_back(CellData::Dot), ++dots;
			else if (currentPixel == sf::Color(0, 250, 0))
				mazeData.push_back(CellData::SuperDot), ++dots;
			else if (currentPixel == sf::Color(255, 242, 0))
			{
				pacmanPosition = sf::Vector2i(x, y);
				mazeData.push_back(CellData::Empty);
			}
			else if (currentPixel == sf::Color(255, 192, 203))
			{
				pinkyPosition = sf::Vector2i(x, y);
				mazeData.push_back(CellData::Empty);
			}
			else if (currentPixel == sf::Color(250, 10, 20))
			{
				blinkyPosition = sf::Vector2i(x, y);
				mazeData.push_back(CellData::Empty);
			}
			else if (currentPixel == sf::Color(255, 140, 0))
			{
				clydePosition = sf::Vector2i(x, y);
				mazeData.push_back(CellData::Empty);
			}
			else if (currentPixel == sf::Color(0, 0, 250))
			{
				inkyPosition = sf::Vector2i(x, y);
				mazeData.push_back(CellData::Empty);
			}
			else if (currentPixel == sf::Color(50, 122, 142))
				mazeData.push_back(CellData::Bonus);
			else
				mazeData.push_back(CellData::Empty);
		}
	}
	
}

sf::Vector2i Maze::getPacmanPosition()
{
	return pacmanPosition;
}

sf::Vector2i Maze::getBlinkyPosition()
{
	return blinkyPosition;
}

sf::Vector2i Maze::getClydePosition()
{
	return clydePosition;
}

sf::Vector2i Maze::getInkyPosition()
{
	return inkyPosition;
}

sf::Vector2i Maze::getPinkyPosition()
{
	return pinkyPosition;
}

unsigned int Maze::positionToIndex(sf::Vector2i position)
{
	return position.y * mazeSize.x + position.x;
}

sf::Vector2i Maze::indexToPosition(unsigned int index)
{
	sf::Vector2i position;

	position.x = index % mazeSize.x;
	position.y = index / mazeSize.x;

	return position;
}

sf::Vector2i Maze::pixelToCell(sf::Vector2f pixel) {

	sf::Vector2i cell;

	cell.x = pixel.x / CELL_SIZE;
	cell.y = pixel.y / CELL_SIZE;

	return cell;

}

sf::Vector2f Maze::cellToPixel(sf::Vector2i cell) {

	sf::Vector2f pixel;

	pixel.x = cell.x * CELL_SIZE + CELL_SIZE / 2;
	pixel.y = cell.y * CELL_SIZE + CELL_SIZE / 2;

	return pixel;

}

void Maze::draw(sf::RenderWindow &window)
{
	
	for (unsigned int i = 0; i < mazeData.size(); i++)
	{
		sf::Vector2i position = indexToPosition(i);

		if (mazeData[i] == CellData::Dot)
		{
			m_Dot.setPosition(cellToPixel(position));
			window.draw(m_Dot);
		}
		else if (mazeData[i] == CellData::SuperDot)
		{
			m_SuperDot.setPosition(cellToPixel(position));
			window.draw(m_SuperDot);
		}
		else if (mazeData[i] == CellData::Bonus)
		{
			Bonus fruit(sheet);
			fruit.drawBonus(window, cellToPixel(position).x, cellToPixel(position).y);
			fruit.drawBonus(window, cellToPixel(position).x, cellToPixel(position).y);
		}
		else if (mazeData[i] == CellData::Wall)
		{
			
			for (int i = 0; i < 4; ++i) {

				if (!isWall(position + neighbor_direction[i])) {

					bound.setRotation(current_angle[i]);
					bound.setPosition(cellToPixel(position));
					window.draw(bound);		

				}

			}

			for (int i = 0; i < 4; ++i) {

				if (!isWall(position + neighbor_direction[i]) && !isWall(position + neighbor_direction[(i + 1) % 4])) {

					outer_bound.setRotation(current_angle[i]);
					outer_bound.setPosition(cellToPixel(position));
					window.draw(outer_bound);

				}

			}

			for (int i = 0; i < 4; ++i) {

				if (isWall(position + neighbor_direction[i]) && isWall(position + neighbor_direction[(i + 1) % 4]) && !isWall(position + corner_direction[i])) {

					inner_bound.setRotation(current_angle[i]);
					inner_bound.setPosition(cellToPixel(position));
					window.draw(inner_bound);

				}

			}
			
		}
	}
}

int Maze::getCellSize() {

	return CELL_SIZE;

}

Maze::~Maze()
{}

int Maze::getDots() {

	return dots;

}

bool Maze::isBlue()
{
	if (is_blue)
	{
		is_blue = false;
		return true;
	}
	return false;
}

bool Maze::noDots() {

	return !dots;

}

void Maze::makeGhostsAlive() {

	is_blue = false;

}