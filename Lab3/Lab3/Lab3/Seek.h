#pragma once
#ifndef SEEK
#define SEEK
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Game.h"

class Game;

class Seek
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
	double static const DEG_TO_RAD;
	double static const RAD_TO_DEG;
private:
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
};

#endif

