#pragma once
#ifndef GAME
#define GAME
#include "Player.h"
#include "Arrive.h"
#include "Seek.h"
#include "Wander.h"
#include "Pursue.h"
#include <SFML/Graphics.hpp>

/// <summary>
/// @brief Main class for the SFML Playground project.
/// 
/// This will be a single class framework for learning about SFML.
/// </summary>
/// 
class Player;
class Arrive;
class Seek;
class Wander;
class Pursue;

class Game
{
public:
	Game();
	void run();
	sf::Vector2f getPlayerPos();
	sf::Vector2f getPlayerVel();
protected:
	void update(double dt);
	void render();
	void processEvents();
	void processGameEvents(sf::Event&);

	// main window
	sf::RenderWindow m_window;
	Player* m_player;
	Seek* m_seek;
	Arrive* m_arrive;
	Wander* m_wander;
	Pursue* m_pursue;
};

#endif