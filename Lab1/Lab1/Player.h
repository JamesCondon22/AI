#pragma once
#include <SFML/Graphics.hpp>
class Player
{
public:
	Player();
	~Player();
	void update(double dt);
	void render(sf::RenderWindow & window);

private:
	sf::Vector2f m_position;
	sf::CircleShape m_circle;
	sf::Vector2f m_velocity;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	int size;
};

