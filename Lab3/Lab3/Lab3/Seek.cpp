#include "Seek.h"

double const Seek::DEG_TO_RAD = 3.14 / 180.0f;
double const Seek::RAD_TO_DEG = 180.0f / 3.14;

Seek::Seek(Game &game) :
	m_game(&game),
	m_position(0, 0),
	m_velocity(0, 0),
	m_rotation(0)
{
	if (!m_texture.loadFromFile("wander.png")) {
		//do something
	}
	m_rect.setTexture(&m_texture);
	m_rect.setOrigin(100, 50);
	m_rect.setSize(sf::Vector2f(200, 100));
	m_rect.setPosition(m_position);
	srand(time(NULL));

}


Seek::~Seek()
{
}

void Seek::checkBorders()
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
void Seek::update(double dt)
{
	checkBorders();
	seek();
	m_position += m_velocity;
	m_rect.setPosition(m_position);
	m_rect.setRotation(m_rotation);



}


void Seek::seek()
{
	m_velocity = m_game->getPlayerPos() - m_position;
	m_velocity = normalise();
	m_velocity = m_velocity * maxSpeed;
	m_rotation = getNewOrientation(m_rotation, m_velocity);
}

float Seek::getNewOrientation(float curOrientation, sf::Vector2f velocity)
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

void Seek::render(sf::RenderWindow & window)
{
	window.draw(m_rect);
}

sf::Vector2f Seek::normalise()
{
	float length = sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y));
	if (length != 0)
		return sf::Vector2f(m_velocity.x / length, m_velocity.y / length);
	else
		return m_velocity;
}

// Returns the length of the vector
float Seek::length(sf::Vector2f vel) {
	return sqrt(vel.x * vel.x + vel.y * vel.y);
}

