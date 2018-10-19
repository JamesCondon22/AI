#pragma once 
#include <SFML/Graphics.hpp>

class Enemy {
public:
	Enemy() {}
	virtual ~Enemy() {}
	virtual void render(sf::RenderWindow & window) = 0;
	virtual void update(double dt) = 0;
	virtual sf::Vector2f getVelocity() = 0;
	virtual sf::Vector2f getPosition() = 0;
	virtual void collisionAvoidance(std::vector<Enemy*> enemy) = 0;
	virtual int getId() = 0;
	
};