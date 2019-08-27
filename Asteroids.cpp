#include "Asteroids.h"


float Asteroid::getVelocityX()
{
	return velocityX;
}

float Asteroid::getVelocityY()
{
	return velocityY;
}

bool Asteroid::getDestroyed()
{
	return destroyed;
}

void Asteroid::setDestroyed(bool newDestroyed)
{
	destroyed = newDestroyed;
}

void Asteroid::offScreenMovementAsteroid(const sf::RenderWindow &window)
{
	// if asteroid's x is less than the size of the window (0)
	if (getPosition().x < 0)
	{
		// asteroid's x is added to the window size
		setPosition(getPosition().x + window.getSize().x, getPosition().y);
	}
	// if asteroid's x is greater than the size of the window (1600)
	if (getPosition().x > window.getSize().x)
	{
		// asteroid's x is subtracted from the window size
		setPosition(getPosition().x - window.getSize().x, getPosition().y);
	}
	// if asteroid's y is less than the size of the window (0)
	if (getPosition().y < 0)
	{
		// asteroid's y is added to the window size
		setPosition(getPosition().x, getPosition().y + window.getSize().y);
	}
	// if asteroid's y is greater than the window size (900)
	if (getPosition().y > window.getSize().y)
	{
		// asteroid's y is subtracted from the window size
		setPosition(getPosition().x, getPosition().y - window.getSize().y);
	}
}


float randomVelocity()
{
	// random direction, creates two random numbers to decide which direction (negative or positive) the asteroid travels
	float randomDirection = rand() % 2;
	if (randomDirection == 0) {
		randomDirection = -1;
	}
	else {
		randomDirection = 1;
	}


	// random number from 0.3 to 0.5
	float random = ((float)rand()) / (float)RAND_MAX;
	// range from 0.5 to 0.3
	float difference = 0.5 - 0.3;
	// multiply random with difference value and direction (-1 or 1)
	float result = random * difference * randomDirection;
	// return 0.3 + result to get range from 0.3 to 0.5
	return (0.3 + result);
}