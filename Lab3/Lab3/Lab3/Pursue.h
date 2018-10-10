#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Game.h"
#include "Enemy.h"

class Game;

class Pursue : public Enemy
{
public:
	Pursue(Game & game);
	Pursue();
	~Pursue();
	float getNewOrientation(float currentOrientation, float velocity);
	void kinematicSeek(sf::Vector2f playerPosition);
	void boundary(float x, float y);
	float getRandom(int x, int y);
	sf::Vector2f collisionAvoidance(std::vector<Enemy*> enemies);
	void update(double dt);
	void render(sf::RenderWindow & window);
	float length(sf::Vector2f vel);
	//Lab3
	void pursue();
	sf::Vector2f normalise(sf::Vector2f vector);
	sf::Vector2f getVelocity();
	sf::Vector2f getPosition();
	int getId();


private:
	Game * m_game;
	float m_timeToTarget;
	float m_orientation;
	float m_rotation;
	float m_velocityF;
	float m_maxSpeed;
	float m_maxRotation;
	float distance;
	float speed;
	float maxTimePrediction;
	float timePrediction;
	sf::Vector2f m_velocity;
	sf::Vector2f m_position;
	
	//Lab3 
	sf::Vector2f direction;
	sf::Vector2f newTarget;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::RectangleShape m_rect;

	int id = 3;
	sf::Vector2f m_relVelocity;
	sf::Vector2f m_relPosition;
	float m_relSpeed;
	float m_timeToCollision;
	float m_minSeperation;
	float m_shortestTime;
	float m_radius;
};