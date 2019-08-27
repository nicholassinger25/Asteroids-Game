#include <SFML/Graphics.hpp>
#include "Asteroids.h"
#include "Collision.h"
#include "Ship.h"
#include "Bullet.h"
#include <time.h>
#include <iostream>
#include <vector>
#include <math.h>

using std::cout;
using std::cin;
using std::endl;


class Game
{
public:
	Game();


	void RunApp();
	void DisplayMenu(); // menu
	void PlayGame(); // play
	void DisplayRules(); // rules
	void TestCases(); // test cases

	void SetUpGame(ship TheShip, const sf::RenderWindow &window); // draws 2 big asteroids, ship, sets values to 0


private:
	int MenuSelection;
	int LevelNumber;
	int Score;
	bool Dead;
	std::vector<Asteroid> bigAsteroids;
	std::vector<Asteroid> mediumAsteroids;
	std::vector<Asteroid> smallAsteroids;
	std::vector<bullet> bullets;
};

// check for collision
template <class T, class R>
bool checkcollision(T &T, R &R)
{

	if (T.getGlobalBounds().intersects(R.getGlobalBounds()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

double deg2rad(double degrees);