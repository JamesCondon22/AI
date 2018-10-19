#include "Enemy.h"

double const Enemy::DEG_TO_RAD = 3.14 / 180.0f;
double const Enemy::RAD_TO_DEG = 180.0f / 3.14;
Enemy::Enemy(Game &game) :
	m_game(&game),
	m_position(0,0),
	m_velocity(0,0),
	m_rotation(0)
{
	if (!m_texture.loadFromFile("enemy.png")) {
		//do something
	}
	m_rect.setTexture(&m_texture);
	m_rect.setOrigin(m_position.x + 100, m_position.y + 50);
	m_rect.setSize(sf::Vector2f(200, 100));
	m_rect.setPosition(m_position);
	srand(time(NULL));
		
}


Enemy::~Enemy()
{
}



void Enemy::wander()
{
	m_velocity = m_game->getPlayerPos() - m_position;
	m_velocity = normalise();
	m_rotation = getNewOrientation(m_rotation, m_velocity);
	m_rotation = m_rotation + maxRotation * ((rand() % 2) - 1);
	m_velocity = sf::Vector2f(-sin(m_rotation), cos(m_rotation)) * maxSpeed;
}
void Enemy::checkBorders()
{
	if (m_rect.getPosition().x > 2020)
	{
		m_position.x = -200;
	}
	if (m_rect.getPosition().x < -200)
	{
		m_position.x = 1920;
	}
	if (m_rect.getPosition().y < -200)
	{
		m_position.y = 1080;
	}
	if (m_rect.getPosition().y > 1180)
	{
		m_position.y = -200;
	}
}
void Enemy::update(double dt)
{
	checkBorders();
	wander();
	m_position += m_velocity;
	m_rect.setPosition(m_position);
	m_rect.setRotation(m_rotation);
	
	

}


float Enemy::getNewOrientation(float curOrientation, sf::Vector2f velocity)
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

void Enemy::render(sf::RenderWindow & window)
{
	window.draw(m_rect);
}

sf::Vector2f Enemy::normalise()
{
	float length = sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y));
	if (length != 0)
		return sf::Vector2f(m_velocity.x / length, m_velocity.y / length);
	else
		return m_velocity;
}
// Returns the length of the vector
float Enemy::length(sf::Vector2f vel) {
	return sqrt(vel.x * vel.x + vel.y * vel.y);
}