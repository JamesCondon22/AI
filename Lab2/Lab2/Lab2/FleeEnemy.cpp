#include "FleeEnemy.h"

double const FleeEnemy::DEG_TO_RAD = 3.14 / 180.0f;
double const FleeEnemy::RAD_TO_DEG = 180.0f / 3.14;

FleeEnemy::FleeEnemy(Game &game) :
	m_game(&game),
	m_position(500, 500),
	m_velocity(0, 0),
	m_rotation(0)
{
	if (!m_texture.loadFromFile("flee.png")) {
		//do something
	}
	m_rect.setTexture(&m_texture);
	m_rect.setSize(sf::Vector2f(200, 100));
	m_rect.setPosition(m_position);
	srand(time(NULL));

}


FleeEnemy::~FleeEnemy()
{
}

void FleeEnemy::flee()
{
	m_velocity = m_position - m_game->getPlayerPos();
	m_velocity = normalise();
	m_velocity = m_velocity * maxSpeed;
	m_rotation = getNewOrientation(m_rotation, m_velocity);
}

void FleeEnemy::checkBorders()
{
	if (m_rect.getPosition().x > 2020)
	{
		m_position.x = 500;
		m_position.y = 500;
	}
	if (m_rect.getPosition().x < -200)
	{
		m_position.x = 500;
		m_position.y = 500;
	}
	if (m_rect.getPosition().y < -200)
	{
		m_position.x = 500;
		m_position.y = 500;
	}
	if (m_rect.getPosition().y > 1180)
	{
		m_position.x = 500;
		m_position.y = 500;
	}
}
void FleeEnemy::update(double dt)
{
	checkBorders();
	flee();
	m_position += m_velocity;
	m_rect.setPosition(m_position);
	m_rect.setRotation(m_rotation);



}


float FleeEnemy::getNewOrientation(float curOrientation, sf::Vector2f velocity)
{
	if (length(velocity) > 0)
	{
		float rotation = atan2(-m_velocity.x, m_velocity.y) * RAD_TO_DEG;
		return rotation;
	}
	else
	{
		return curOrientation;
	}
}

void FleeEnemy::render(sf::RenderWindow & window)
{
	window.draw(m_rect);
}

sf::Vector2f FleeEnemy::normalise()
{
	float length = sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y));
	if (length != 0)
		return sf::Vector2f(m_velocity.x / length, m_velocity.y / length);
	else
		return m_velocity;
}
// Returns the length of the vector
float FleeEnemy::length(sf::Vector2f vel) {
	return sqrt(vel.x * vel.x + vel.y * vel.y);
}

