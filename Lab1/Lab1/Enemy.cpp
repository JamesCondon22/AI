#include "Enemy.h"


Enemy::Enemy() :
	m_position(100,100),
	m_velocity(0,0)
{

	m_rect.setOutlineColor(sf::Color::Red);
	m_rect.setSize(sf::Vector2f(100, 100));
	m_rect.setOutlineThickness(10);
	m_rect.setPosition(m_position);
	srand(time(NULL));
	m_velocity.x = (rand() % 20) - 10;
	m_velocity.y = (rand() % 20) - 10;
		
}


Enemy::~Enemy()
{
}

void Enemy::update(double dt)
{
	m_position.x += m_velocity.x;
	m_position.y += m_velocity.y;
	m_rect.setPosition(m_position.x ,m_position.y);
	std::cout << m_velocity.x << std::endl;

	if (m_rect.getPosition().x > 1920)
	{
		m_position.x = 0;
	}
	if (m_rect.getPosition().x < -200)
	{
		m_position.x = 1920;
	}
	if (m_rect.getPosition().y < -200)
	{
		m_position.y = 1080;
	}
	if (m_rect.getPosition().y > 1080)
	{
		m_position.y = 0;
	}

}

void Enemy::render(sf::RenderWindow & window)
{
	window.draw(m_rect);
}
