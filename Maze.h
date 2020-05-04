#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Dot.h"

class Maze
{
public:

	Maze();

	~Maze();

	void loadLevel(std::string file);
	// @param the level image file name
	// loads the level image and iterates on it pixel by pixel and add the pixels
	// colors to the m_mazeData vector as they're defind to their Entities

	sf::Vector2i getPacmanPosition();
	// @return Pacman's position
	sf::Vector2i getBlinkyPosition();
	// @return Blinky's position
	sf::Vector2i getPinkyPosition();
	// @return Pinky's positions
	sf::Vector2i getInkyPosition();
	// @return Inky's positions
	sf::Vector2i getClydePosition();
	// @return Clyde's positions

	inline unsigned int positionToIndex(sf::Vector2i position);
	// @param a 2d vector carries a position
	// @return unsigned int the index of the position in the m_mazeData vector

	inline sf::Vector2i indexToPosition(unsigned int index);
	// @param an unsigned int carries the index in the m_mazeData vector
	// @return a 2d vector the position of the index in the maze

	bool isWall(sf::Vector2i position);

	sf::Vector2i pixelToCell(sf::Vector2f pixel);

	sf::Vector2f cellToPixel(sf::Vector2i cell);

	void draw(sf::RenderWindow &window);

	int getCellSize();

	bool removeDot(sf::Vector2i cell);

	bool removeBonus(sf::Vector2i cell);

	bool removeSuperDot(sf::Vector2i cell);

	bool noDots();

	int getDots();

	bool isBlue();

	void makeGhostsAlive();

	bool isValid(sf::Vector2i position);

	void set_volume(bool);

private:

	enum class CellData
	{
		Empty, Wall, Dot, SuperDot, Bonus
	};
	// to make the code more readable instead of using plain integers 
	// using enum class as it's safer than plain enum Avoiding possible bugs and confusion
	
	sf::Vector2i mazeSize;
	std::vector<CellData> mazeData;
	sf::Vector2i pacmanPosition, blinkyPosition, pinkyPosition, inkyPosition, clydePosition;
	sf::Texture wallPicture, sheet;
	sf::Sprite bound, inner_bound, outer_bound;
	int dots;
	bool is_blue, volume_on;
	sf::Sound pacman_chomp, pacman_eatfruit;
	sf::SoundBuffer pacman_chomp_buffer, pacman_eatfruit_buffer;
	sf::CircleShape m_Dot, m_SuperDot;

};

