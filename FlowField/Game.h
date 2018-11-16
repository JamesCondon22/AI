#pragma once
#ifndef GAME
#define GAME
#include <SFML/Graphics.hpp>


#include "Tile.h"


class Game
{
public:
	Game();
	void run();
protected:
	void update(double dt);
	void render();
	void processEvents();
	void processGameEvents(sf::Event&);

	// main window
	sf::RenderWindow m_window;
	//std::vector<Tile*> m_tiles;
	Tile *m_tile[50][50];
	Tile *m_starttile;
	Tile *m_goaltile;
	sf::Mouse mouse;
	sf::Font m_font;
	bool Leftpressed = false;
	bool Rightpressed = false;
};

#endif