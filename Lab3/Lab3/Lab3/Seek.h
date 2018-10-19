#pragma once
#ifndef SEEK
#define SEEK
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Game.h"
#include "Enemy.h"

class Game;

class Seek : public Enemy
{
public:
	Seek(Game & game);
	~Seek();
	void update(double dt);
	void render(sf::RenderWindow & window);
	float getNewOrientation(float currentOrientation, sf::Vector2f velocity);
	sf::Vector2f normalise();
	float length(sf::Vector2f vel);
	void seek();
	void checkBorders();
	sf::Vector2f getVelocity();
	sf::Vector2f getPosition();
	void collisionAvoidance(std::vector<Enemy*> enemy);
	int getId();
	void initFont();
	double static const DEG_TO_RAD;
	double static const RAD_TO_DEG;
private:
	int id = 1;
	sf::Vector2f m_direction;
	float m_distance;
	sf::Vector2f m_position;
	sf::RectangleShape m_rect;
	sf::Vector2f m_velocity;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	Game *m_game;
	sf::Vector2f m_playerPos;
	float m_rotation;
	float maxSpeed = 2;
	float maxRotation = 180;
	sf::Text m_label;
	sf::Font m_font;
	float m_radius;

	float m_threshold;
	int m_behaviour;
};

#endif

