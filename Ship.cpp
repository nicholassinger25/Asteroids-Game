#include "Ship.h"
ship::ship(const sf::Color &newcolor, int newhealth, const sf::RenderWindow &window, bool newshooooooted)
{
	setFillColor(newcolor);
	health = newhealth;

	setPointCount(3);
	setPoint(0, sf::Vector2f(15 + window.getSize().x / 2, 0 + window.getSize().y / 2));
	setPoint(1, sf::Vector2f(window.getSize().x / 2, 50 + window.getSize().y / 2));
	setPoint(2, sf::Vector2f(30 + window.getSize().x / 2, 50 + window.getSize().y / 2));
	shoooooooted = newshooooooted;

}
bool  ship::getshoooted()
{
	return shoooooooted;
}
void ship::setShooted(bool newval)
{
	shoooooooted = newval;
}
ship::~ship()
{
	//lmao; 
}


double deg2rad(double degrees)
{
	return degrees * 4.0 * atan(1.0) / 180.0;
}

void ship::rotateR()
{
	rotate(.4f);
}
void ship::rotateLeft()
{
	rotate(-.4f);
}
void ship::moveforward()
{
	move((sin(deg2rad(getRotation()))), -cos(deg2rad(getRotation())));

}
void ship::moveback()
{
	move((-sin(deg2rad(getRotation()))), cos(deg2rad(getRotation())));
	checkrotate();

}

void  ship::checkrotate()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		rotateR();

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		rotateLeft();
	}
}

void ship::checkpositon()
{
	if (getPosition().y < 0)//these if statements are to throw the ship to the other side of the screen if it hits the edge.
	{
		setPosition(getPosition().x, 899);
	}
	else if (getPosition().y > 899)
	{
		setPosition(getPosition().x, 0);
	}
	if (getPosition().x < -5)
	{
		setPosition(1620, getPosition().y);
	}
	else if (getPosition().x > 1621)
	{
		setPosition(-4, getPosition().y);
	}
}

int ship::gethealth()
{
	return health;
}

void ship::sethealth(int newhealth)
{
	health = newhealth;
}


