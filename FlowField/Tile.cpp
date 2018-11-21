#include "Tile.h"



Tile::Tile(int x, int y, sf::Font & m_font, int dx, int dy) :
	m_position(x,y),
	posX(dx),
	posY(dy),
	m_gridPos(dx,dy),
	m_cost(0),
	isObstacle(false)

{
	
	m_rect.setSize(sf::Vector2f(50.0,50.0));
	m_rect.setPosition(m_position);
	m_rect.setOutlineColor(sf::Color::Black);
	m_rect.setOutlineThickness(2.0f);
	line[0] = sf::Vector2f(m_position.x + 25, m_position.y + 25);
	line[1] = sf::Vector2f(m_position);
	line->color = sf::Color::Black;
	//m_line = sf::Vector2f(150, 5);
	
	m_label.setFont(m_font);
	m_label.setCharacterSize(20);
	m_label.setString(std::to_string(m_cost));
	m_label.setPosition(m_position);
	m_label.setFillColor(sf::Color(0, 0, 0));
}


Tile::~Tile()
{
}


void Tile::changeColor()
{
	
}

void Tile::setObstacle()
{
	isObstacle = true;
	m_current = Obstacles::Obstacle;
}

void Tile::update(double dt)
{

}

void Tile::render(sf::RenderWindow & window)
{
	/*if (m_current == Obstacles::Start)
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
	}*/
	window.draw(m_rect);
	window.draw(m_label);
	if (!isObstacle)
	window.draw(line, 2, sf::Lines);
	
}

void Tile::setGoal()
{
	if (m_current != Obstacles::Obstacle)
	{
		m_current = Obstacles::Goal;
	}
}

void Tile::setStart()
{
	if (m_current != Obstacles::Obstacle)
	{
		m_current = Obstacles::Start;
	}
}

void Tile::setCost(int num)
{
	m_cost = num;
	m_label.setString(std::to_string(m_cost));
}
sf::Vector2f Tile::getPosition()
{
	return m_position;
}
int Tile::getXpos() {
	return posX;
}

int Tile::getYpos() {
	return posY;
}

void Tile::setVisited(bool visit) {
	available = visit;
}

void Tile::setPos(int x, int y) {
	m_gridPos.first = x;
	m_gridPos.second = y;
}

void Tile::setColor(sf::Color col)
{
	m_rect.setFillColor(sf::Color(col));
}

void Tile::setVectorPosition(std::pair<int,int> pos)
{
	/*if (pos.first > m_gridPos.first && pos.second == m_gridPos.second)
	{
		line[1] = sf::Vector2f(line[0].position.x + 25, line[0].position.y);
	}
	if (pos.first < m_gridPos.first && pos.second == m_gridPos.second)
	{
		line[1] = sf::Vector2f(line[0].position.x - 25, line[0].position.y);
	}*/
	if (pos.first == m_gridPos.first && pos.second > m_gridPos.second)
	{
		line[1] = sf::Vector2f(line[0].position.x, line[0].position.y + 25);
	}
	if (pos.first == m_gridPos.first && pos.second < m_gridPos.second)
	{
		line[1] = sf::Vector2f(line[0].position.x, line[0].position.y - 25);
	}

	/*if (pos.first < m_gridPos.first && pos.second < m_gridPos.second)
	{
		line[1] = sf::Vector2f(line[0].position.x + 25, line[0].position.y +25);
	}*/
		
}

void Tile::initVectors()
{
	vectors[0] = sf::Vector2f(m_position);
	vectors[1] = sf::Vector2f(m_position.x + 25, m_position.y);
	vectors[2] = sf::Vector2f(m_position.x + 50, m_position.y);
	vectors[3] = sf::Vector2f(m_position.x + 50, m_position.y + 25);
	vectors[4] = sf::Vector2f(m_position.x + 50, m_position.y + 50);
	vectors[5] = sf::Vector2f(m_position.x + 25, m_position.y + 50);
	vectors[6] = sf::Vector2f(m_position.x , m_position.y + 50);
	vectors[7] = sf::Vector2f(m_position.x, m_position.y + 25);
	vectors[8] = sf::Vector2f(m_position.x + 25, m_position.y + 25);
}