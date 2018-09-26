#pragma once
#ifndef GAME
#define GAME
#include "Enemy.h"
#include "SeekEnemy.h"
#include "FleeEnemy.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

/// <summary>
/// @brief Main class for the SFML Playground project.
/// 
/// This will be a single class framework for learning about SFML.
/// </summary>
/// 
class Enemy;
class FleeEnemy;
class SeekEnemy;
class Player;


class Game
{
public:
	Game();
	void run();
	sf::Vector2f getPlayerPos();
protected:
	void update(double dt);
	void render();
	void processEvents();
	void processGameEvents(sf::Event&);

	// main window
	sf::RenderWindow m_window;
	Player* m_player;
	Enemy* m_wanderEnemy;
	SeekEnemy* m_seekEnemy;
	FleeEnemy* m_fleeEnemy;
};

#endif