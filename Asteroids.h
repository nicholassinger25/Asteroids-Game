#pragma once

#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <vector>

class Asteroid : public sf::CircleShape
{
public:
	Asteroid(float radius, std::size_t pointCount, sf::Vector2f &pos, float velx, float vely)
		: sf::CircleShape(radius, pointCount)
	{
		this->setFillColor(sf::Color(32, 32, 32));
		this->setPosition(pos);
		this->setOutlineColor(sf::Color(64, 64, 64));
		this->setOutlineThickness(2);
		velocityX = velx;
		velocityY = vely;
		destroyed = false;

	}


	float getVelocityX();
	float getVelocityY();
	bool getDestroyed();

	void setDestroyed(bool newDestroyed);


	void offScreenMovementAsteroid(const sf::RenderWindow &window);
private:
	float velocityX;
	float velocityY;
	bool destroyed;
};

float randomVelocity();