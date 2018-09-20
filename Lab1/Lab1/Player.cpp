#include "Player.h"



Player::Player() :
	m_position(500,500),
	m_velocity(0,0),
	size(100)
{
	m_circle.setRadius(float(size));
	m_circle.setOutlineColor(sf::Color::Green);
	m_circle.setOutlineThickness(10);
	m_circle.setPosition(m_position);
}


Player::~Player()
{
}

void Player::update(double dt)
{

	m_circle.setPosition(m_circle.getPosition().x + m_velocity.x, m_circle.getPosition().y + m_velocity.y);

	//key presses 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		//std::cout << 
		m_velocity.x -= .003f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_velocity.x += .003f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_velocity.y -= .003f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_velocity.y += .003f;
	}

	//looping screen 
	if (m_circle.getPosition().x > 1920)
	{
		m_circle.setPosition(-100, m_circle.getPosition().y);
	}
	if (m_circle.getPosition().x < -200)
	{
		m_circle.setPosition(1920, m_circle.getPosition().y);
	}
	if (m_circle.getPosition().y < -200)
	{
		m_circle.setPosition(m_circle.getPosition().y, 1080);
	}
	if (m_circle.getPosition().y > 1080)
	{
		m_circle.setPosition(m_circle.getPosition().y, 0);
	}
}

void Player::render(sf::RenderWindow & window)
{
	window.draw(m_circle);
}
