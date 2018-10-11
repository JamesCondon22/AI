#pragma once
#ifndef GAME
#define GAME
#include "Player.h"
#include "Pursue.h"
#include "Arrive.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>

/// <summary>
/// @brief Main class for the SFML Playground project.
/// 
/// This will be a single class framework for learning about SFML.
/// </summary>
/// 

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
	void collisionAvoid();

	// main window
	sf::RenderWindow m_window;
	Player* m_player;
	

	std::vector<Enemy*> m_enemies;
};

#endif