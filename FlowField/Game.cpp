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
	: m_window(sf::VideoMode(1250, 1250, 32), "SFML Playground", sf::Style::Default)

{

	m_window.setVerticalSyncEnabled(true);
	
	if (!m_font.loadFromFile("Adventure.otf"))
	{
		std::cout << "problem loading font" << std::endl;
	}
	mouse.setPosition(sf::Vector2i(0, 0), m_window);
	
	int x = 0;
	int y = 0;

	for (int i = 0; i <= 50; i++) {
		for (int j = 0; j <= 50; j++) {	 
			m_tile[i][j] = new Tile(x,y,m_font);
			x += 25;
			if (x > 1250) {
				y += 25;
				x = 0;
			}
			//m_tiles.push_back(m_tile);
		}	
	}
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
	
	//mouse.getPosition();

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		Leftpressed = false;
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		Rightpressed = false;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !Leftpressed)
	{
		Leftpressed = true;
		if (mouse.getPosition(m_window).x > 0 && mouse.getPosition(m_window).x < 1250) {
			if (mouse.getPosition(m_window).y > 0 && mouse.getPosition(m_window).y < 1250) {
				int x = mouse.getPosition(m_window).x / 25;
				int y = mouse.getPosition(m_window).y / 25;
				std::cout << x << ", " << y << std::endl;
				m_starttile->changeColor();
				m_starttile = m_tile[y][x];
				m_tile[y][x]->setStart();
			}
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !Rightpressed) {
		Rightpressed = true;
		if (mouse.getPosition(m_window).x > 0 && mouse.getPosition(m_window).x < 1250) {
			if (mouse.getPosition(m_window).y > 0 && mouse.getPosition(m_window).y < 1250) {
				int x = mouse.getPosition(m_window).x / 25;
				int y = mouse.getPosition(m_window).y / 25;
				std::cout << x << ", " << y << std::endl;
				m_goaltile->changeColor();
				m_goaltile = m_tile[y][x];
				m_tile[y][x]->setGoal();
			}
		}
	}
}

/// <summary>
/// Method to handle all game updates
/// </summary>
/// <param name="time">update delta time</param>
void Game::update(double dt)
{
	sf::Time deltaTime;
	
	
	//std::cout << mouse.getPosition(m_window).x << std::endl;
	
}






/// <summary>
/// @brief draw the window for the game.
/// 
/// draw buttons and text on left side
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);

	for (int x = 0; x < 50; x++) {
		for (int y = 0; y < 50; y++) {

			m_tile[x][y]->render(m_window);
		}
	
	}
	m_window.display();
}


