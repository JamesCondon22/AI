#include "Pursue.h"

Pursue::Pursue(Game & game) :
	m_game(&game),
	m_position(500, 500),
	m_velocity(0, 0),
	m_maxSpeed(2.0f),
	m_maxRotation(20.0f),
	m_timeToTarget(100.0f),
	maxTimePrediction(250.0f),
	m_relPosition(0,0),
	m_radius(50)
{

	if (!m_texture.loadFromFile("wander.png")) {
		//error
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_sprite.setScale(0.3, 0.3);
	m_velocity.x = getRandom(20, -10);
	m_velocity.y = getRandom(20, -10);

	m_sprite.setOrigin(m_position.x - (m_sprite.getTextureRect().width / 2), m_position.y - (m_sprite.getTextureRect().height / 2));

}

Pursue::Pursue()
{

}


Pursue::~Pursue()
{

}

float Pursue::getNewOrientation(float currentOrientation, float velocity)
{
	if (velocity >0)
	{
		return (std::atan2(-m_velocity.x, m_velocity.y) * 180.0 / 3.141592653589793238463);
	}
	else {
		return currentOrientation;
	}

}
sf::Vector2f Pursue::collisionAvoidance(std::vector<Enemy*> enemies)
{
	m_shortestTime = INT_MAX;

	//Enemy* enemy = new Pursue(*m_game);
	sf::Vector2f enemy = sf::Vector2f(NULL, NULL);
	float firstMin = 0;
	float firstDistance = 0;
	sf::Vector2f firstRelPos = sf::Vector2f(0,0);
	sf::Vector2f firstRelVel = sf::Vector2f(0,0);

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
		std::cout << "colliding" << std::endl;
	}
	else
	{
		m_relPosition = firstRelPos + firstRelVel * m_shortestTime;
	}
	
	m_relPosition = normalise(m_relPosition);
	m_velocity = m_relPosition * 10.0f;
	return m_velocity;
}
void Pursue::boundary(float x, float y)
{
	if (x > 2100)
	{
		m_position.x = -100;
	}
	if (x < -100)
	{
		m_position.x = 2100;
	}
	if (y < -100)
	{
		m_position.y = 2100;
	}
	if (y > 2100)
	{
		m_position.y = -100;
	}

}

float Pursue::getRandom(int a, int b)
{
	srand(time(NULL));
	float randVal = rand() % a + b;
	return randVal;
}

void Pursue::kinematicSeek(sf::Vector2f playerPosition)
{
	m_velocity = playerPosition - m_position;
	//Get magnitude of vector
	m_velocityF = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);

	//Normalize vector
	m_velocity.x = m_velocity.x / m_velocityF;
	m_velocity.y = m_velocity.y / m_velocityF;

	m_velocity.x = m_velocity.x * m_maxSpeed;
	m_velocity.y = m_velocity.y * m_maxSpeed;

	m_orientation = getNewOrientation(m_orientation, m_velocityF);

}


void Pursue::pursue()
{
	direction = m_game->getPlayerPos() - m_position;
	distance = std::sqrt(direction.x*direction.x + direction.y* direction.y);
	speed = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);

	if (speed <= distance / maxTimePrediction)
	{
		timePrediction = maxTimePrediction;
	}
	else {
		timePrediction = distance / speed;
	}

	newTarget = m_game->getPlayerPos() + m_game->getPlayerVel() * timePrediction;

	kinematicSeek(newTarget);
}


void Pursue::update(double dt)
{
	pursue();

	m_position = m_position + m_velocity;

	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_orientation);

	boundary(m_sprite.getPosition().x, m_sprite.getPosition().y);
}


void Pursue::render(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

sf::Vector2f Pursue::getPosition()
{
	return m_sprite.getPosition();
}
sf::Vector2f Pursue::getVelocity()
{
	return m_velocity;
}
int Pursue::getId()
{
	return id;
}
// Returns the length of the vector
float Pursue::length(sf::Vector2f vel) {
	return sqrt(vel.x * vel.x + vel.y * vel.y);
}
sf::Vector2f Pursue::normalise(sf::Vector2f vec)
{
	float length = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	if (length != 0)
		return sf::Vector2f(vec.x / length, vec.y / length);
	else
		return vec;
}