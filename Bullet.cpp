#include"Bullet.h"

bullet::bullet(const sf::Vector2f &pos, float velx, float vely, float radius)
{
	setFillColor(sf::Color::White);
	setRadius(radius);
	position = pos;
	setPosition(pos);
	this->velx = velx;
	this->vely = vely;
	alive = true;

}

bool bullet::bulletdeletion(const sf::RenderWindow &window, int location)
{
	if (getPosition().x < 0)
	{
		return true;
	}
	if (getPosition().x > window.getSize().x)
	{
		return true;
	}
	if (getPosition().y < 0)
	{
		return true;
	}
	if (getPosition().y > window.getSize().y)
	{
		return true;
	}
	return false;
}



bool bullet::getalive()
{
	return alive;
}

void bullet::setalive(bool newalive)
{
	alive = newalive;
}


float bullet::getvelx()
{
	return velx;
}

float bullet::getvely()
{
	return vely;
}