#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

enum Obstacles
{
	Goal,
	Start,
	Path,
	Obstacle,
	Blank
};
class Tile
{
public:
	Tile(int x, int y, sf::Font & m_font);
	~Tile();
	void update(double dt);
	void render(sf::RenderWindow &window);
	void changeColor();
	void setGoal();
	void setStart();
	void setObstacle();
private:
	sf::RectangleShape m_rect;
	sf::Vector2f m_position;
	sf::Text m_label;

	bool m_selected = false;
	Obstacles m_current;
	Obstacles m_previous;
};

