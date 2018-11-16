#include "Tile.h"



Tile::Tile(int x, int y, sf::Font & m_font) :
	m_position(x,y)
{
	
	m_rect.setSize(sf::Vector2f(25.0,25.0));
	m_rect.setPosition(m_position);
	m_rect.setOutlineColor(sf::Color::Black);
	m_rect.setOutlineThickness(2.0f);

	m_label.setFont(m_font);
	m_label.setCharacterSize(20);
	m_label.setString("0");
	m_label.setPosition(m_position);
	m_label.setFillColor(sf::Color(0, 0, 0));
}


Tile::~Tile()
{
}


void Tile::changeColor()
{
	m_current = Obstacles::Blank;
}

void Tile::setObstacle()
{
	m_current = Obstacles::Obstacle;
}

void Tile::update(double dt)
{

}

void Tile::render(sf::RenderWindow & window)
{
	if (m_current == Obstacles::Start)
	{
		m_rect.setFillColor(sf::Color::Green);
	}
	if (m_current == Obstacles::Goal)
	{
		m_rect.setFillColor(sf::Color::Red);
	}
	if (m_current == Obstacles::Obstacle)
	{
		m_rect.setFillColor(sf::Color::Black);
	}
	if (m_current == Obstacles::Blank)
	{
		m_rect.setFillColor(sf::Color::White);
	}
	window.draw(m_rect);
	window.draw(m_label);
	
}

void Tile::setGoal()
{
	m_current = Obstacles::Goal;
}

void Tile::setStart()
{
	m_current = Obstacles::Start;
}
