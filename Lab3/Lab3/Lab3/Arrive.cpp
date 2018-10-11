#include "Arrive.h"

double const Arrive::DEG_TO_RAD = 3.14 / 180.0f;
double const Arrive::RAD_TO_DEG = 180.0f / 3.14;

Arrive::Arrive(Game &game) :
	m_game(&game),
	m_position(0, 0),
	m_velocity(0, 0),
	m_rotation(0),
	maxSpeed(2.0f),
	timeToTarget(80.0f),
	m_radius(50)
{
	if (!m_texture.loadFromFile("wander.png")) {
		//do something
	}
	m_rect.setTexture(&m_texture);
	m_rect.setOrigin(100, 50);
	m_rect.setSize(sf::Vector2f(200, 100));
	m_position = sf::Vector2f(1920, 0);
	m_rect.setPosition(m_position);
	srand(time(NULL));

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
	arrive();
	m_position += m_velocity;
	m_rect.setPosition(m_position);
	m_rect.setRotation(m_orientation);
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
}


sf::Vector2f Arrive::getPosition()
{
	return m_sprite.getPosition();
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


sf::Vector2f Arrive::collisionAvoidance(std::vector<Enemy*> enemies)
{
	m_shortestTime = INT_MAX;
	//Enemy* enemy = new Arrive(*m_game);
	sf::Vector2f enemy = sf::Vector2f(NULL, NULL);
	float firstMin = 0;
	float firstDistance = 0;
	sf::Vector2f firstRelPos = sf::Vector2f(0, 0);
	sf::Vector2f firstRelVel = sf::Vector2f(0, 0);

	for (int i = 0; i < enemies.size(); i++)
	{
		m_relPosition = enemies[i]->getPosition() - m_position;
		m_relVelocity = enemies[i]->getVelocity() - m_velocity;
		m_relSpeed = length(m_relVelocity);
		m_timeToCollision = ((m_relPosition.x * m_relVelocity.x) + (m_relPosition.y * m_relVelocity.y)) /
			(m_relSpeed * m_relSpeed);
		distance = length(m_relPosition);
		m_minSeperation = distance - m_relSpeed * m_shortestTime;

		if (m_minSeperation > (m_radius * m_radius))
		{
			break;
		}
		if (m_timeToCollision > 0 && m_timeToCollision < m_shortestTime)
		{
			m_shortestTime = m_timeToCollision;
			enemy = enemies[i]->getPosition();
			firstMin = m_minSeperation;
			firstDistance = distance;
			firstRelPos = m_relPosition;
			firstRelVel = m_relVelocity;
		}	
	}
	if (enemy == sf::Vector2f(NULL, NULL))
	{
		return sf::Vector2f();
	}
	
	if (firstMin <= 0 || distance < (m_radius*m_radius))
	{
		m_relPosition = enemy - m_position;
		//std::cout << "colliding" << std::endl;
	}
	else
	{
		m_relPosition = firstRelPos + firstRelVel * m_shortestTime;
	}
	m_relPosition = normalise(m_relPosition);
	m_velocity = m_relPosition * 10.0f;
	return m_velocity;
}
	
	

	

