#include "Seek.h"

double const Seek::DEG_TO_RAD = 3.14 / 180.0f;
double const Seek::RAD_TO_DEG = 180.0f / 3.14;

Seek::Seek(Game &game) :
	m_game(&game),
	m_position(0, 0),
	m_velocity(0, 0),
	m_rotation(0),
	m_radius(75.0f),
	m_threshold(30.0f),
	m_behaviour(1)
{
	if (!m_texture.loadFromFile("wander.png")) {
		//do something
	}

	if (!m_font.loadFromFile("Adventure.otf"))
	{
		std::cout << "problem loading font" << std::endl;
	}
	initFont();
	m_rect.setTexture(&m_texture);
	m_rect.setOrigin(100, 50);
	m_rect.setSize(sf::Vector2f(100, 75));
	m_rect.setPosition(m_position);
	m_position = sf::Vector2f(1920, 1080);
	srand(time(NULL));

}

void Seek::initFont()
{
	m_label.setFont(m_font);
	m_label.setCharacterSize(40);
	m_label.setString("Seek");
	m_label.setPosition(m_rect.getPosition());
	m_label.setFillColor(sf::Color(0, 0, 0));
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
	if (m_behaviour == 1)
	{
		seek();
	}
	m_position += m_velocity;
	m_rect.setPosition(m_position);
	m_rect.setRotation(m_rotation);

	m_label.setPosition(m_rect.getPosition().x - 50, m_rect.getPosition().y - 130);

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
	window.draw(m_label);
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

void Seek::collisionAvoidance(std::vector<Enemy*> enemies) {

	///Closest approach



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
					m_rotation -= 180;
				}


			}
			if (m_behaviour == 2 && m_distance > m_radius * 2)
			{
				m_behaviour = 1;
			}



		}
	}

}



sf::Vector2f Seek::getPosition()
{
	return m_rect.getPosition();
}
sf::Vector2f Seek::getVelocity()
{
	return m_velocity;
}
int Seek::getId()
{
	return id;
}

