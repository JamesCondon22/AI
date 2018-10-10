#pragma once
#ifndef ARRIVE
#define ARRIVE
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Game.h"

class Game;

class Arrive
{
public:
	Arrive(Game & game);
	~Arrive();
	void update(double dt);
	void render(sf::RenderWindow & window);
	float getNewOrientation(float currentOrientation, float velocity);
	sf::Vector2f normalise();
	float length(sf::Vector2f vel);
	void arrive();
	void checkBorders();
	double static const DEG_TO_RAD;
	double static const RAD_TO_DEG;
private:
	sf::Vector2f m_position;
	sf::RectangleShape m_rect;
	sf::Vector2f m_velocity;
	float m_velocityF;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	Game *m_game;
	sf::Vector2f m_playerPos;
	float m_rotation;
	float maxSpeed;
	float maxRotation = 0;
	float timeToTarget = 100;
	float m_orientation;
};

#endif

