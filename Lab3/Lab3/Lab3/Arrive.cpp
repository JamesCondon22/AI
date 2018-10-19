#include "Arrive.h"

double const Arrive::DEG_TO_RAD = 3.14 / 180.0f;
double const Arrive::RAD_TO_DEG = 180.0f / 3.14;

Arrive::Arrive(Game &game, float speedTime) :
	m_game(&game),
	m_position(0, 0),
	m_velocity(0, 0),
	m_rotation(0),
	maxSpeed(2.0f),
	timeToTarget(speedTime),
	m_radius(75.0f),
	m_threshold(30.0f),
	m_behaviour(1),
	m_startTimer(false)
{
	if (!m_texture.loadFromFile("wander.png")) {
		//do something
	}
	if (!m_font.loadFromFile("Adventure.otf"))
	{
		std::cout << "problem loading font" << std::endl;
	}

	m_rect.setTexture(&m_texture);
	m_rect.setOrigin(100, 50);
	m_rect.setSize(sf::Vector2f(100, 75));
	m_position = sf::Vector2f(1920, 0);
	m_rect.setPosition(m_position);
	srand(time(NULL));

	initFont();
}

void Arrive::initFont()
{
	m_label.setFont(m_font);
	m_label.setCharacterSize(40);
	m_label.setString("Arrive");
	m_label.setPosition(m_rect.getPosition());
	m_label.setFillColor(sf::Color(0, 0, 0));
}

Arrive::~Arrive()
{
}

void Arrive::checkBorders()
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

void Arrive::update(double dt)
{
	checkBorders();
	if (m_behaviour == 1)
	{
		arrive();
	}
	m_position += m_velocity;
	m_rect.setPosition(m_position);
	m_rect.setRotation(m_orientation);

	if (m_startTimer)
	{
		m_time += m_clock.restart().asMilliseconds();
	}
	else
	{
		m_seconds = 0;
	}
	if (m_time > 1000)
	{
		m_seconds += 1;
		m_time = 0;
	}
	std::cout << m_seconds << std::endl;
	//resetting label postions
	m_label.setPosition(m_rect.getPosition().x - 50, m_rect.getPosition().y - 130);
}

void Arrive::arrive()
{
	//Get magnitude of vector
	m_velocityF = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);

	m_velocity = m_game->getPlayerPos() - m_position;

	if (m_velocityF >= 0)
	{
		m_velocity = m_velocity / timeToTarget;

		if (m_velocityF > maxSpeed) {

			//Normalize vector
			m_velocity.x = m_velocity.x / m_velocityF;
			m_velocity.y = m_velocity.y / m_velocityF;

			m_velocity = m_velocity * maxSpeed;

		}

		m_orientation = getNewOrientation(m_orientation, m_velocityF);
	}
}

float Arrive::getNewOrientation(float curOrientation, float velocity)
{
	if (velocity > 0)
	{
		float rotation = atan2(-m_velocity.x, m_velocity.y) * RAD_TO_DEG;
		return rotation;
	}
	else
	{
		return curOrientation;
	}
}

void Arrive::render(sf::RenderWindow & window)
{
	window.draw(m_rect);
	window.draw(m_label);
}


sf::Vector2f Arrive::getPosition()
{
	return m_rect.getPosition();
}
sf::Vector2f Arrive::getVelocity()
{
	return m_velocity;
}
int Arrive::getId()
{
	return id;
}
// Returns the length of the vector
float Arrive::length(sf::Vector2f vel) {
	return sqrt(vel.x * vel.x + vel.y * vel.y);
}
sf::Vector2f Arrive::normalise(sf::Vector2f vec)
{
	float length = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	if (length != 0)
		return sf::Vector2f(vec.x / length, vec.y / length);
	else
		return vec;
}

void Arrive::collisionAvoidance(std::vector<Enemy*> enemies)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->getPosition() != m_position)
		{
			//Vector player to enemy
			m_direction = enemies[i]->getPosition() - m_position;
			m_distance = std::sqrt(m_direction.x*m_direction.x + m_direction.y* m_direction.y);



			if (m_distance <= m_radius)
			{
				float dot = (m_velocity.x * m_direction.x) + (m_velocity.y * m_direction.y);
				float det = (m_velocity.x * m_direction.y) - (m_velocity.y * m_direction.x);

				float angle = atan2(det, dot);
				angle = (180 / 3.14) * angle;



				if (angle >= -m_threshold && angle <= m_threshold)
				{
					m_behaviour = 2;
					m_velocity = -m_velocity;
					m_orientation -=180;

				}


			}
			if (m_behaviour == 2 && m_distance > m_radius * 2)
			{
				m_behaviour = 1;
				
			}

			

		}
	}
}
	

	

