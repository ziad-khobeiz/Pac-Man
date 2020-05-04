#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include "Menu.h"
#include "SingleMenu.h"
#include "Dot.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Maze.h"
#include "Finished.h"
#include "Ready.h"
#include "Bonus.h"
#include "GameSound.h"
#include "PauseMenu.h"
#include "StatusBar.h"
#include "NameMenu.h"
#include <fstream>
#include "Scoreboard.h"

#define LEVELS 3

using namespace sf;
using namespace std;

const float VIEW_HEIGHT = 512;

bool volume_on = true;
bool fromPauseMode;

enum {

	StartMenu, SinglePlayerMenu, AboutUs, SoundMenu, ScoreboardMenu, 
	SinglePlayerMode, MultiplayerMode, FinishedGame, GetReady, PausedMenu, EnterNameMenu

};

int currentMenu, currentLevel;

int main() {
     
	sf::RenderWindow window(sf::VideoMode(18 * 50, 19 * 50), "Pac-Man");

	Menu menu(window.getSize().x, window.getSize().y);
	SingleMenu singleMenu(window.getSize().x, window.getSize().y);
	Finished finishedMenu(window.getSize().x, window.getSize().y);
	Ready readyMenu(window.getSize().x, window.getSize().y);
	GameSound gameSound(window.getSize().x, window.getSize().y);
	PauseMenu pauseMenu(window.getSize().x, window.getSize().y);
	Scoreboard scoreboard(window.getSize().x, window.getSize().y);
	Texture sheet;
	Texture credits;
	credits.loadFromFile("assets/credits.png");
	Sprite aboutUs;
	aboutUs.setTexture(credits);
	Texture logoTexture;
	logoTexture.loadFromFile("assets/logo.png");
	Sprite logo;
	logo.setTexture(logoTexture);
	logo.setPosition({ float(window.getSize().x) / 2, 75 });
	logo.setOrigin(logo.getGlobalBounds().width / 2, logo.getGlobalBounds().height / 2 );
	sheet.loadFromFile("assets/sheet.png");
	sheet.setSmooth(true);
	Maze maze;
	currentLevel = 1;
	maze.loadLevel("level1");
	Pacman pacman(sheet);
	NameMenu nameMenu(window.getSize().x, window.getSize().y);
	pacman.setMaze(&maze);
	StatusBar statusBar(sheet, &pacman);
	Ghost blinky(sheet, 0, &pacman);
	Ghost pinky(sheet, 1, &pacman);
	Ghost inky(sheet, 2, &pacman);
	Ghost clyde(sheet, 3, &pacman);
	pacman.setMaze(&maze);
	blinky.setMaze(&maze);
	inky.setMaze(&maze);
	pinky.setMaze(&maze);
	clyde.setMaze(&maze);

	sf::SoundBuffer pacman_beginning_buffer;
	pacman_beginning_buffer.loadFromFile("assets/pacman_beginning.wav");
	sf::Sound pacman_beginning(pacman_beginning_buffer);
	pacman_beginning.play();
	pacman_beginning.setLoop(1);
	pacman_beginning.setVolume(20);
	sf::Time blue_time = sf::seconds(10);

	Clock clock;

	while (window.isOpen())
	{

		sf::Event event;

		sf::Time deltaTime = clock.getElapsedTime();
		clock.restart();

		while (window.pollEvent(event))
		{

			if (event.type == event.Closed) window.close();

			if (currentMenu == StartMenu)
			{

				if (event.type == Event::KeyReleased)
				{
					if (event.key.code == Keyboard::Up) menu.MoveUp();
					else if (event.key.code == Keyboard::Down) menu.MoveDown();
					else if (event.key.code == Keyboard::Return)
					{

						if (menu.getPressedItem() == 0) currentMenu = SinglePlayerMenu;
						else if (menu.getPressedItem() == 1) fromPauseMode = false, currentMenu = SoundMenu;
						else if (menu.getPressedItem() == 2) currentMenu = AboutUs;
						else window.close();

					}
				}

			}
			else if (currentMenu == SinglePlayerMenu) {

				if (event.type == Event::KeyReleased) {
					if (event.key.code == Keyboard::Up) singleMenu.MoveUp();
					else if (event.key.code == Keyboard::Down) singleMenu.MoveDown();
					else if (event.key.code == Keyboard::Return) {

						if (singleMenu.getPressedItem() == 0) currentMenu = GetReady;
						else if (singleMenu.getPressedItem() == 1) currentMenu = ScoreboardMenu;
						else currentMenu = StartMenu;

					}
				}

			}
			else if (currentMenu == AboutUs) {


				if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape) currentMenu = StartMenu;

			}
			else if (currentMenu == SoundMenu) {

				if (event.type == Event::KeyReleased) {
					if (event.key.code == Keyboard::Up) gameSound.MoveUp();
					else if (event.key.code == Keyboard::Down) gameSound.MoveDown();
					else if (event.key.code == Keyboard::Return) {
						if (gameSound.getPressedItem() == 0)
						{
							if (volume_on)
								pacman_beginning.setVolume(0);
							else
								pacman_beginning.setVolume(20);

							volume_on = 1 - volume_on;

							maze.set_volume(volume_on);
							inky.set_volume(volume_on);
							blinky.set_volume(volume_on);
							pinky.set_volume(volume_on);
							clyde.set_volume(volume_on);
							gameSound.setString(volume_on);
						}
						else if (fromPauseMode) currentMenu = PausedMenu;
						else currentMenu = StartMenu;

					}
				}

			}
			else if (currentMenu == ScoreboardMenu)
			{
				if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape) {
					currentMenu = SinglePlayerMenu;
				}
			}
			else if (currentMenu == SinglePlayerMode) {

				if (event.type == Event::KeyReleased) {

					if (event.key.code == Keyboard::Up) pacman.setDirection(sf::Vector2i(0, -1));
					else if (event.key.code == Keyboard::Down) pacman.setDirection(sf::Vector2i(0, 1));
					else if (event.key.code == Keyboard::Left) pacman.setDirection(sf::Vector2i(-1, 0));
					else if (event.key.code == Keyboard::Right) pacman.setDirection(sf::Vector2i(1, 0));
					else if (event.key.code == Keyboard::Escape) {
						fromPauseMode = true;
						currentMenu = PausedMenu;
						pacman_beginning.play();
						if (volume_on)
							pacman_beginning.setVolume(20);
						else
							pacman_beginning.setVolume(0);
					}

				}

			}
			else if (currentMenu == MultiplayerMode) {

				// Multiplayer mode code
				// To be implemented.

			}
			else if (currentMenu == FinishedGame) {

				if (event.type == Event::KeyReleased) {
					if (event.key.code == Keyboard::Up) finishedMenu.MoveUp();
					else if (event.key.code == Keyboard::Down) finishedMenu.MoveDown();
					else if (event.key.code == Keyboard::Return) {
						if (finishedMenu.getPressedItem() == 0) currentMenu = ScoreboardMenu;
						else currentMenu = StartMenu;

					}
				}

			}
			else if (currentMenu == PausedMenu) {

				if (event.type == Event::KeyReleased)
				{
					if (event.key.code == Keyboard::Up) pauseMenu.MoveUp();
					else if (event.key.code == Keyboard::Down) pauseMenu.MoveDown();
					else if (event.key.code == Keyboard::Return)
					{

						if (pauseMenu.getPressedItem() == 0) currentMenu = SinglePlayerMode;
						else if (pauseMenu.getPressedItem() == 1) currentMenu = SoundMenu;
						else if (pauseMenu.getPressedItem() == 2) {
							currentMenu = StartMenu;
							maze.loadLevel("level1");
							pacman.setMaze(&maze);
							clyde.setMaze(&maze);
							inky.setMaze(&maze);
							pinky.setMaze(&maze);
							blinky.setMaze(&maze);
							clyde.makeAlive();
							inky.makeAlive();
							pinky.makeAlive();
							blinky.makeAlive();
							maze.makeGhostsAlive();
						}
						else window.close();

					}
				}

			}
			else if (currentMenu == EnterNameMenu)
			{
				if (event.type == Event::TextEntered)
				{
					nameMenu.TypeOn(event);
				}
				else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Return && !nameMenu.getString().empty()) {

					currentMenu = FinishedGame;
					nameMenu.addToFile();
				}
			}
		}

		window.clear();
		if (currentMenu == StartMenu)
			menu.draw(window);
		else if (currentMenu == SinglePlayerMenu)
			singleMenu.draw(window);
		else if (currentMenu == AboutUs)
			window.draw(aboutUs);
		else if (currentMenu == SoundMenu)
			gameSound.draw(window);
		else if (currentMenu == SinglePlayerMode)
		{

			pacman_beginning.pause();

			if (maze.noDots() || pacman.isDead()) {

				if (currentLevel == LEVELS || pacman.isDead()) {
					finishedMenu.changeString(maze.getDots() ? "You lost!" : "You won!");
					currentMenu = EnterNameMenu;
					currentLevel = 1;
					nameMenu.setScore(pacman.getScore());
					nameMenu.setTime(pacman.getTime());
					pacman.reset();
				}
				else {

					currentMenu = GetReady;
					currentLevel++;

				}

				pacman_beginning.play();
				if (volume_on)
					pacman_beginning.setVolume(20);
				else
					pacman_beginning.setVolume(0);
				maze.loadLevel("level" + std::to_string(currentLevel));
				pacman.setMaze(&maze);
				clyde.setMaze(&maze);
				inky.setMaze(&maze);
				pinky.setMaze(&maze);
				blinky.setMaze(&maze);
				clyde.makeAlive();
				inky.makeAlive();
				pinky.makeAlive();
				blinky.makeAlive();
				maze.makeGhostsAlive();
				// refresh pacman

			}

			maze.draw(window);

			if (pacman.isDying()) {

				clyde.setMaze(&maze);
				inky.setMaze(&maze);
				pinky.setMaze(&maze);
				blinky.setMaze(&maze);
				clyde.makeAlive();
				inky.makeAlive();
				pinky.makeAlive();
				blinky.makeAlive();
				maze.makeGhostsAlive();

			}

			if (maze.isBlue())
			{
				clyde.makeBlue(blue_time);
				inky.makeBlue(blue_time);
				pinky.makeBlue(blue_time);
				blinky.makeBlue(blue_time);
			}

			pacman.update(deltaTime);
			pacman.draw(window);
			statusBar.draw(window);
			clyde.update(deltaTime);
			clyde.draw(window);
			inky.update(deltaTime);
			inky.draw(window);
			blinky.update(deltaTime);
			blinky.draw(window);
			pinky.update(deltaTime);
			pinky.draw(window);

		}
		else if (currentMenu == FinishedGame) {
			finishedMenu.draw(window);
		}
		else if (currentMenu == GetReady) {
			if (readyMenu.update(deltaTime)) currentMenu = SinglePlayerMode;
			readyMenu.draw(window);
		}
		else if (currentMenu == PausedMenu) {
			pauseMenu.draw(window);
		}
		else if (currentMenu == EnterNameMenu) {
			nameMenu.draw(window);
		}
		else if (currentMenu == ScoreboardMenu) {
			scoreboard.draw(window);
		}

		if (currentMenu == SinglePlayerMenu || currentMenu == AboutUs || currentMenu == SoundMenu || currentMenu == StartMenu) {
			window.draw(logo);
		}
		

		window.display();
		
	}

	return 0;
}