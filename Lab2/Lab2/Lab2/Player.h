#pragma once
#include <SFML/Graphics.hpp>
class Player
{
public:
	Player();
	~Player();
	void update(double dt);
	void render(sf::RenderWindow & window);
	void increaseRotation();
	void decreaseRotation();
	void increaseSpeed();
	void decreaseSpeed();
private:
	sf::Vector2f m_position;
	sf::RectangleShape m_rect;
	sf::Vector2f m_velocity;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	int size;
	double static const DEG_TO_RAD;
	double m_rotation;
	double m_speed;
	double MAX_SPEED;
	sf::Vector2f m_heading;
};

