#pragma once
#include"SFML\Graphics.hpp"
#include <vector>

#ifndef BULLET_H
#define BULLET_H
class bullet :public sf::CircleShape
{
public:
	/*Constructors*/
	bullet(const sf::Vector2f &pos, float velx, float vely, float radius);

	bool getalive();
	void setalive(bool newalive);

	bool bulletdeletion(const sf::RenderWindow &window, int location);

	float getvelx();
	float getvely();
	
private:
	float velx;
	float vely;
	sf::Vector2f position;
	bool alive;
	
};
#endif 