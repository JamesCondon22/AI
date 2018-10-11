#include "Game.h"

/// <summary>
/// @author RP
/// @version 1.0
/// 
/// </summary>

// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;

/// <summary>
/// @brief Default constructor.
/// 
/// Create a new window and initialise member objects.
/// </summary>
/// 
Game::Game()
	: m_window(sf::VideoMode(1920, 1080, 32), "SFML Playground", sf::Style::Default)

{

	m_window.setVerticalSyncEnabled(true);
	int currentLevel = 1;

	m_player = new Player();
	Enemy* m_pursue = new Pursue(*this);
	Enemy* m_arrive = new Arrive(*this);


	m_enemies.push_back(m_pursue);
	m_enemies.push_back(m_arrive);
}



/// <summary>
/// Main game entry point - runs until user quits.
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();

		lag += dt.asMilliseconds();

		processEvents();

		while (lag > MS_PER_UPDATE)
		{
			update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;
		}
		update(MS_PER_UPDATE);

		render();
	}
}



/// <summary>
/// @brief Check for events
/// 
/// Allows window to function and exit. 
/// Events are passed on to the Game::processGameEvents() method
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		processGameEvents(event);
	}
}
/// <summary>
/// @brief Handle all user input.
/// 
/// Detect and handle keyboard input.
/// </summary>
/// <param name="event">system event</param>
void Game::processGameEvents(sf::Event& event)
{


}

/// <summary>
/// Method to handle all game updates
/// </summary>
/// <param name="time">update delta time</param>
void Game::update(double dt)
{
	sf::Time deltaTime;
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->update(dt);
		m_enemies[i]->collisionAvoidance(m_enemies);
	}
	m_player->update(dt);


}

void Game::collisionAvoid()
{
	for (int i = 0; i < m_enemies.size(); i++)
	{
		
		m_enemies[i]->collisionAvoidance(m_enemies);
	}
	
}




sf::Vector2f Game::getPlayerPos()
{
	return m_player->getPos();
}

sf::Vector2f Game::getPlayerVel()
{
	return m_player->getVel();
}


/// <summary>
/// @brief draw the window for the game.
/// 
/// draw buttons and text on left side
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0));
	m_player->render(m_window);
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->render(m_window);
	}
	m_window.display();
}


