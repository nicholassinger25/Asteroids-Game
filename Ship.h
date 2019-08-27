#pragma once
#include<SFML/Graphics.hpp>
#include "Bullet.h"
#include <vector>

class ship :public sf::ConvexShape
{
public: ship(const sf::Color &newcolor, int newhealth, const sf::RenderWindow &window, bool newshooooooted = false);
		~ship();
		bool shoot(const sf::RenderWindow &window);
		void setShooted(bool newval);
		bool getshoooted();
		void rotateR();
		void rotateLeft();
		void moveforward();
		void moveback();
		void checkrotate();
		void checkpositon();
		int gethealth();
		void sethealth(int newhealth);
private:
	int health;
	int shoooooooted;

};