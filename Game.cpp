#include "Game.h"

Game::Game()
{
	MenuSelection = 0;
	LevelNumber = 1;
	Score = 0;
	Dead = false;
}

void Game::RunApp()
{
	do {
		DisplayMenu();
		cin >> MenuSelection;
		switch (MenuSelection) {
		case 1: // play game
			PlayGame();

			system("pause");
			system("cls");
			break;
		case 2: // display rules
			DisplayRules();

			system("pause");
			system("cls");
			break;

		case 3: // test cases
			TestCases();

			system("pause");
			system("cls");
			break;
		case 4: // exit program
			cout << "Exiting Program. . ." << endl;

			break;
		default:
			cout << "Error: Invalid selection." << endl;

			system("pause");
			system("cls");
			break;
		}
	} while (MenuSelection != 4);
}

void Game::DisplayMenu()
{
	cout << "==========Welcome to Asteroids==========" << endl;
	cout << "1. Play Game" << endl << endl;
	cout << "2. Show Rules" << endl << endl;
	cout << "3. Test Cases" << endl << endl;
	cout << "4. Exit Game" << endl << endl;
	cout << "========================================" << endl;
}

void Game::DisplayRules()
{
	system("cls");
	cout << "==========Rules of Asteroids==========" << endl;
	cout << "1. You start out as a ship in the middle of the screen." << endl;
	cout << "2. At first, there are 2 big asteroids that spawn on the screen that you must shoot to destory." << endl;
	cout << "3. Destroying a big asteroid spawns 2 medium asteroids, and destroyed a medium asteroid spawns 2 small asteroids." << endl;
	cout << "4. You start with 3 lifes and crashing into an asteroid reduces your lifes by 1." << endl;
	cout << "5. Destroyed asteroids adds points to your score" << endl;
	cout << "6. Destroying all asteroids on current stage will give you a bonus of 1000 points and spawn an additional big asteroid each time." << endl;
	cout << "7. Big Asteroid - 20 Points\t Medium Asteroid - 50 Points\t Small Asteroid - 100 Points" << endl;
	cout << "8. Try to survive and earn as many points as you can!" << endl;
	cout << "======================================" << endl;
}

void Game::PlayGame()
{
	system("cls");
	srand((unsigned int)time(NULL));
	sf::RenderWindow window(sf::VideoMode(1600, 900), "Asteroids");
	sf::Clock clock;
	int destroyedLocationBig = 0, destroyedLocationMedium = 0, destroyedLocationSmall = 0, destroyedLocationBullet = 0;
	int n = 0, j = 0;
	float tempx, tempy, tempx1, tempy1, tempx2, tempy2, tempx3, tempy3;
	sf::Vector2f tempShipPos;
	ship TheShip(sf::Color::White, 3, window,false);

	window.clear();

	SetUpGame(TheShip, window);

	window.draw(TheShip);

	for (auto &a : bigAsteroids)
	{
		window.draw(a);
	}

	window.display();

	while (window.isOpen())
	{
		float x = TheShip.getPoint(0).x + TheShip.getPoint(1).x + TheShip.getPoint(2).x;
		x = x / 3;
		float y = TheShip.getPoint(0).y + TheShip.getPoint(1).y + TheShip.getPoint(2).y;
		y = y / 3;

		for (; n<1; n++)
		{

			TheShip.setOrigin(x, y);
			TheShip.setPosition(window.getSize().x / 2, window.getSize().y / 2);
		}
		window.clear();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			TheShip.rotateR();

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			TheShip.rotateLeft();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			TheShip.checkrotate();
			TheShip.moveforward();
			TheShip.checkpositon();
			TheShip.checkrotate();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			TheShip.checkrotate();
			TheShip.moveback();
			TheShip.checkpositon();
			TheShip.checkrotate();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				TheShip.checkrotate();
				TheShip.moveforward();
				TheShip.checkpositon();
				TheShip.checkrotate();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				TheShip.checkrotate();
				TheShip.moveback();
				TheShip.checkpositon();
				TheShip.checkrotate();
			}

			tempx = 2.5 * sin(deg2rad(TheShip.getRotation()));
			tempy = 2.5 * -cos(deg2rad(TheShip.getRotation()));
			tempShipPos = TheShip.getPosition();
			if (bullets.size() < 1)
			{
				bullets.push_back(bullet(tempShipPos, tempx, tempy, 5));
			}
		}
		window.clear();
		for (auto &b : bullets)
		{
			b.move(b.getvelx(), b.getvely());
			window.draw(b);
		}

		for (auto &a : bigAsteroids)
		{
			window.draw(a);
			a.offScreenMovementAsteroid(window);
			a.move(a.getVelocityX(), a.getVelocityY());
		}
		// draws, checks if offscreen, and moves asteroids in medium asteroid vector
		for (auto &a : mediumAsteroids)
		{
			window.draw(a);
			a.offScreenMovementAsteroid(window);
			a.move(a.getVelocityX(), a.getVelocityY());
		}
		// draws, checks if offscreen, and moves asteroids in small asteroid vector
		for (auto &a : smallAsteroids)
		{
			window.draw(a);
			a.offScreenMovementAsteroid(window);
			a.move(a.getVelocityX(), a.getVelocityY());
		}
		window.draw(TheShip);

		window.display();

		// checks if all asteroids are destroyed, then adds to score
		if (bigAsteroids.empty() && mediumAsteroids.empty() && smallAsteroids.empty())
		{
			LevelNumber++;
			Score += 1000;
			for (int i = 0; i < LevelNumber + 1; i++)
			{
				bigAsteroids.push_back(Asteroid(64.f, 15, sf::Vector2f(1400.0, rand() % 900), randomVelocity(), randomVelocity()));
			}
		}


		// checks if asteroids are destroyed
		int i = 0;
		// for big asteroids
		for (auto &a : bigAsteroids) // loops function that passes destroyedLocationBig as ref and passes mediumAsteroids vector and bigAsteroids vector
		{
			for (auto &b : bullets)
			{
				int j = 0;
				destroyedLocationBig = 0, destroyedLocationBullet = 0;
				// check collision with bullet, if true then execute this (pressing space is for testing)
				if (checkcollision(b, a))
				{
					// destroyed is true, so can erase later
					// destroyedLocation gives location in vector to erase later
					a.setDestroyed(true);
					b.setalive(false);
					destroyedLocationBig = i;
					destroyedLocationBullet = j;

					// delete bullet
					b.setPosition(-100, -100);

					// sets temp values of velocity and position to create the smaller asteroids
					sf::Vector2f tempVector(a.getPosition().x, a.getPosition().y);


					// creates 2 medium asteroids to new vector
					mediumAsteroids.push_back(Asteroid(32.f, 15, sf::Vector2f(tempVector), randomVelocity(), randomVelocity()));
					mediumAsteroids.push_back(Asteroid(32.f, 15, sf::Vector2f(tempVector), randomVelocity(), randomVelocity()));
				}
				j++;
				window.clear();

				for (auto &b : bullets)
				{
					b.move(b.getvelx(), b.getvely());
					window.draw(b);
				}

				for (auto &a : bigAsteroids)
				{
					window.draw(a);
					a.offScreenMovementAsteroid(window);
					a.move(a.getVelocityX(), a.getVelocityY());
				}
				// draws, checks if offscreen, and moves asteroids in medium asteroid vector
				for (auto &a : mediumAsteroids)
				{
					window.draw(a);
					a.offScreenMovementAsteroid(window);
					a.move(a.getVelocityX(), a.getVelocityY());
				}
				// draws, checks if offscreen, and moves asteroids in small asteroid vector
				for (auto &a : smallAsteroids)
				{
					window.draw(a);
					a.offScreenMovementAsteroid(window);
					a.move(a.getVelocityX(), a.getVelocityY());
				}
				window.draw(TheShip);

				window.display();
			}
			i++;
			window.clear();
			for (auto &b : bullets)
			{
				b.move(b.getvelx(), b.getvely());
				window.draw(b);
			}

			for (auto &a : bigAsteroids)
			{
				window.draw(a);
				a.offScreenMovementAsteroid(window);
				a.move(a.getVelocityX(), a.getVelocityY());
			}
			// draws, checks if offscreen, and moves asteroids in medium asteroid vector
			for (auto &a : mediumAsteroids)
			{
				window.draw(a);
				a.offScreenMovementAsteroid(window);
				a.move(a.getVelocityX(), a.getVelocityY());
			}
			// draws, checks if offscreen, and moves asteroids in small asteroid vector
			for (auto &a : smallAsteroids)
			{
				window.draw(a);
				a.offScreenMovementAsteroid(window);
				a.move(a.getVelocityX(), a.getVelocityY());
			}
			window.draw(TheShip);

			window.display();
		}
		i = 0;
		// for medium asteroids
		for (auto &a : mediumAsteroids)
		{
			int j = 0;
			destroyedLocationMedium = 0, destroyedLocationBullet = 0;
			for (auto &b : bullets)
			{
				// check collision with bullet, if true then execute this (pressing space is for testing)
				if (checkcollision(b, a))
				{
					a.setDestroyed(true);
					b.setalive(false);
					destroyedLocationMedium = i;
					destroyedLocationBullet = j;
					sf::Vector2f tempVector(a.getPosition().x, a.getPosition().y);

					b.setPosition(-100, -100);

					// creates 2 small asteroids to new vector
					smallAsteroids.push_back(Asteroid(16.f, 15, sf::Vector2f(tempVector), randomVelocity(), randomVelocity()));
					smallAsteroids.push_back(Asteroid(16.f, 15, sf::Vector2f(tempVector), randomVelocity(), randomVelocity()));
				}
				j++;
				window.clear();

				for (auto &b : bullets)
				{
					b.move(b.getvelx(), b.getvely());
					window.draw(b);
					window.display();
				}

				for (auto &a : bigAsteroids)
				{
					window.draw(a);
					a.offScreenMovementAsteroid(window);
					a.move(a.getVelocityX(), a.getVelocityY());
				}
				// draws, checks if offscreen, and moves asteroids in medium asteroid vector
				for (auto &a : mediumAsteroids)
				{
					window.draw(a);
					a.offScreenMovementAsteroid(window);
					a.move(a.getVelocityX(), a.getVelocityY());
				}
				// draws, checks if offscreen, and moves asteroids in small asteroid vector
				for (auto &a : smallAsteroids)
				{
					window.draw(a);
					a.offScreenMovementAsteroid(window);
					a.move(a.getVelocityX(), a.getVelocityY());
				}
				window.draw(TheShip);

				window.display();
			}
			i++;
			window.clear();
			for (auto &b : bullets)
			{
				b.move(b.getvelx(), b.getvely());
				window.draw(b);
			}

			for (auto &a : bigAsteroids)
			{
				window.draw(a);
				a.offScreenMovementAsteroid(window);
				a.move(a.getVelocityX(), a.getVelocityY());
			}
			// draws, checks if offscreen, and moves asteroids in medium asteroid vector
			for (auto &a : mediumAsteroids)
			{
				window.draw(a);
				a.offScreenMovementAsteroid(window);
				a.move(a.getVelocityX(), a.getVelocityY());
			}
			// draws, checks if offscreen, and moves asteroids in small asteroid vector
			for (auto &a : smallAsteroids)
			{
				window.draw(a);
				a.offScreenMovementAsteroid(window);
				a.move(a.getVelocityX(), a.getVelocityY());
			}
			window.draw(TheShip);

			window.display();
		}

		i = 0;
		// for small asteroids
		for (auto &a : smallAsteroids)
		{
			int j = 0;
			destroyedLocationSmall = 0, destroyedLocationBullet = 0;
			for (auto &b : bullets)
			{
				// check collision with bullet, if true then execute this (pressing space is for testing)
				if (checkcollision(b, a))
				{
					a.setDestroyed(true);
					b.setalive(false);
					destroyedLocationSmall = i;
					destroyedLocationBullet = j;
					b.setPosition(-100, -100);
				}
				j++;
				window.clear();

				for (auto &b : bullets)
				{
					b.move(b.getvelx(), b.getvely());
					window.draw(b);
					window.display();
				}

				for (auto &a : bigAsteroids)
				{
					window.draw(a);
					a.offScreenMovementAsteroid(window);
					a.move(a.getVelocityX(), a.getVelocityY());
				}
				// draws, checks if offscreen, and moves asteroids in medium asteroid vector
				for (auto &a : mediumAsteroids)
				{
					window.draw(a);
					a.offScreenMovementAsteroid(window);
					a.move(a.getVelocityX(), a.getVelocityY());
				}
				// draws, checks if offscreen, and moves asteroids in small asteroid vector
				for (auto &a : smallAsteroids)
				{
					window.draw(a);
					a.offScreenMovementAsteroid(window);
					a.move(a.getVelocityX(), a.getVelocityY());
				}
				window.draw(TheShip);

				window.display();
			}
			i++;
			window.clear();
			for (auto &b : bullets)
			{
				b.move(b.getvelx(), b.getvely());
				window.draw(b);
			}

			for (auto &a : bigAsteroids)
			{
				window.draw(a);
				a.offScreenMovementAsteroid(window);
				a.move(a.getVelocityX(), a.getVelocityY());
			}
			// draws, checks if offscreen, and moves asteroids in medium asteroid vector
			for (auto &a : mediumAsteroids)
			{
				window.draw(a);
				a.offScreenMovementAsteroid(window);
				a.move(a.getVelocityX(), a.getVelocityY());
			}
			// draws, checks if offscreen, and moves asteroids in small asteroid vector
			for (auto &a : smallAsteroids)
			{
				window.draw(a);
				a.offScreenMovementAsteroid(window);
				a.move(a.getVelocityX(), a.getVelocityY());
			}
			window.draw(TheShip);

			window.display();
		}


		// check for end of screen
		int location = 0;
		bool bulletdel = false;
		for (auto b = bullets.begin(); b != bullets.end();)
		{
			bulletdel = b->bulletdeletion(window, location);
			if (bulletdel == true)
			{
				b->setalive(false);
				b++;
			}
			else
			{
				b++;
			}
			location++;
		}
		window.clear();
		for (auto &b : bullets)
		{
			b.move(b.getvelx(), b.getvely());
			window.draw(b);
		}

		for (auto &a : bigAsteroids)
		{
			window.draw(a);
			a.offScreenMovementAsteroid(window);
			a.move(a.getVelocityX(), a.getVelocityY());
		}
		// draws, checks if offscreen, and moves asteroids in medium asteroid vector
		for (auto &a : mediumAsteroids)
		{
			window.draw(a);
			a.offScreenMovementAsteroid(window);
			a.move(a.getVelocityX(), a.getVelocityY());
		}
		// draws, checks if offscreen, and moves asteroids in small asteroid vector
		for (auto &a : smallAsteroids)
		{
			window.draw(a);
			a.offScreenMovementAsteroid(window);
			a.move(a.getVelocityX(), a.getVelocityY());
		}
		window.draw(TheShip);

		window.display();



		//deletes asteroids that are destroyed

		// if big asteroid is destroyed
		for (auto a = bigAsteroids.begin(); a != bigAsteroids.end();) {
			if (a->getDestroyed())
			{
				Score += 20;
				// erase it from vector
				
				a = bigAsteroids.erase(bigAsteroids.begin() + destroyedLocationBig);
				//a++;
			}
			else {
				// else increment thru vector
				a++;
			}
		}

		// if medium asteroid is destroyed
		for (auto a = mediumAsteroids.begin(); a != mediumAsteroids.end();) {
			if (a->getDestroyed())
			{
				Score += 50;
				// erase it from vector
				a = mediumAsteroids.erase(mediumAsteroids.begin() + destroyedLocationMedium);
			}
			else {
				// else iterate thru vector
				a++;
			}
		}

		// if small asteroid is destroyed
		for (auto a = smallAsteroids.begin(); a != smallAsteroids.end();) {
			if (a->getDestroyed())
			{
				Score += 100;
				// erase it from vector
				a = smallAsteroids.erase(smallAsteroids.begin() + destroyedLocationSmall);
			}
			else {
				// else iterate thru vector
				a++;
			}
		}

		// if bullet goes off screen
		for (auto b = bullets.begin(); b != bullets.end();) {
			if (!b->getalive())
			{
				// erase it from vector
				b = bullets.erase(bullets.begin() + destroyedLocationBullet);
			}
			else {
				// else iterate thru vector
				b++;
			}
		}



		// check collisions with ship
		bool hit1 = false; 
		for (auto &a : bigAsteroids)
		{
			
			while(checkcollision(a, TheShip) || hit1==true)
			{
				if (j == 0)
				{
					clock.restart();
					j++; 
				}
				hit1 = true; 
				TheShip.setOrigin(-300, -300);
				sf::Time elapsed = clock.getElapsedTime();

				window.clear();
				for (auto &a : bigAsteroids)
				{
					window.draw(a);
					a.offScreenMovementAsteroid(window);
					a.move(a.getVelocityX(), a.getVelocityY());
				}
				// draws, checks if offscreen, and moves asteroids in medium asteroid vector
				for (auto &a : mediumAsteroids)
				{
					window.draw(a);
					a.offScreenMovementAsteroid(window);
					a.move(a.getVelocityX(), a.getVelocityY());
				}
				// draws, checks if offscreen, and moves asteroids in small asteroid vector
				for (auto &a : smallAsteroids)
				{
					window.draw(a);
					a.offScreenMovementAsteroid(window);
					a.move(a.getVelocityX(), a.getVelocityY());
				}

				window.display();

				if (elapsed.asSeconds() >= 3)
				{
					TheShip.setPosition(window.getSize().x / 2, window.getSize().y / 2);
					TheShip.setOrigin(x, y);
					TheShip.sethealth(TheShip.gethealth() - 1);
					hit1 = false; 
					j = 0; 

				}
			}
		}

		bool hit2 = false;
		for (auto &a : mediumAsteroids)
		{

			while (checkcollision(a, TheShip) || hit2 == true)
			{
				if (j == 0)
				{
					clock.restart();
					j++;
				}
				hit2 = true;
				TheShip.setOrigin(-300, -300);
				sf::Time elapsed = clock.getElapsedTime();

				window.clear();
				for (auto &a : bigAsteroids)
				{
					window.draw(a);
					a.offScreenMovementAsteroid(window);
					a.move(a.getVelocityX(), a.getVelocityY());
				}
				// draws, checks if offscreen, and moves asteroids in medium asteroid vector
				for (auto &a : mediumAsteroids)
				{
					window.draw(a);
					a.offScreenMovementAsteroid(window);
					a.move(a.getVelocityX(), a.getVelocityY());
				}
				// draws, checks if offscreen, and moves asteroids in small asteroid vector
				for (auto &a : smallAsteroids)
				{
					window.draw(a);
					a.offScreenMovementAsteroid(window);
					a.move(a.getVelocityX(), a.getVelocityY());
				}

				for (auto &b : bullets)
				{
					window.draw(b);
					b.move(b.getvelx(), b.getvely());
				}

				window.display();

				if (elapsed.asSeconds() >= 3)
				{
					TheShip.setPosition(window.getSize().x / 2, window.getSize().y / 2);
					TheShip.setOrigin(x, y);
					TheShip.sethealth(TheShip.gethealth() - 1);
					hit2 = false;
					j = 0;

				}
			}
		}
	

		bool hit3 = false;
		for (auto &a : smallAsteroids)
		{

			while (checkcollision(a, TheShip) || hit3 == true)
			{
				if (j == 0)
				{
					clock.restart();
					j++;
				}
				hit3 = true;
				TheShip.setOrigin(-300, -300);
				sf::Time elapsed = clock.getElapsedTime();

				window.clear();
				for (auto &a : bigAsteroids)
				{
					window.draw(a);
					a.offScreenMovementAsteroid(window);
					a.move(a.getVelocityX(), a.getVelocityY());
				}
				// draws, checks if offscreen, and moves asteroids in medium asteroid vector
				for (auto &a : mediumAsteroids)
				{
					window.draw(a);
					a.offScreenMovementAsteroid(window);
					a.move(a.getVelocityX(), a.getVelocityY());
				}
				// draws, checks if offscreen, and moves asteroids in small asteroid vector
				for (auto &a : smallAsteroids)
				{
					window.draw(a);
					a.offScreenMovementAsteroid(window);
					a.move(a.getVelocityX(), a.getVelocityY());
				}

				window.display();

				if (elapsed.asSeconds() >= 3)
				{
					TheShip.setPosition(window.getSize().x / 2, window.getSize().y / 2);
					TheShip.setOrigin(x, y);
					TheShip.sethealth(TheShip.gethealth() - 1);
					hit3 = false;
					j = 0;

				}
			}
		}

		window.clear();

		for (auto &b : bullets)
		{
			b.move(b.getvelx(), b.getvely());
			window.draw(b);
			window.display();
		}

		for (auto &a : bigAsteroids)
		{
			window.draw(a);
			a.offScreenMovementAsteroid(window);
			a.move(a.getVelocityX(), a.getVelocityY());
		}
		// draws, checks if offscreen, and moves asteroids in medium asteroid vector
		for (auto &a : mediumAsteroids)
		{
			window.draw(a);
			a.offScreenMovementAsteroid(window);
			a.move(a.getVelocityX(), a.getVelocityY());
		}
		// draws, checks if offscreen, and moves asteroids in small asteroid vector
		for (auto &a : smallAsteroids)
		{
			window.draw(a);
			a.offScreenMovementAsteroid(window);
			a.move(a.getVelocityX(), a.getVelocityY());
		}
		window.draw(TheShip);

		window.display();

		if (TheShip.gethealth() == 0)
		{
			Dead = true;
		}

		if (Dead)
		{
			window.close();
			bigAsteroids.clear();
			mediumAsteroids.clear();
			smallAsteroids.clear();
			bullets.clear();
			cout << "==========Game Over!==========" << endl;
			cout << "Total Score: " << Score << endl;
		}
	}
}

void Game::TestCases()
{
	system("cls");

	cout << "==========Test Cases==========" << endl;
	cout << "Test Case 1: Spawning Asteroids. . ." << endl;
	bigAsteroids.push_back(Asteroid(64.f, 15, sf::Vector2f(1400.0, rand() % 900), randomVelocity(), randomVelocity()));
	if (!bigAsteroids.empty())
	{
		cout << "Successfully pushed one asteroid into the asteroid vector!" << endl << endl;
	}
	else
	{
		cout << "Error: Was unsuccessful to push one asteroid into the asteroid vector." << endl << endl;
	}

	cout << "Test Case 2: Deleting Asteroids. . ." << endl;
	bigAsteroids.clear();
	if (bigAsteroids.empty())
	{
		cout << "Successfully deleted asteroid in the vector!" << endl << endl;
	}
	else
	{
		cout << "Error: Was unsuccessful to delete asteroid in the vector." << endl << endl;
	}

	cout << "Test Case 3: Spawning Bullets. . ." << endl;
	bullets.push_back(bullet(sf::Vector2f(100, 100), 100, 100, 5));
	if (!bullets.empty())
	{
		cout << "Successfully pushed one bullet into the bullet vector!" << endl << endl;
	}
	else
	{
		cout << "Error: Was unsuccessful to push one bullet into the bullet vector." << endl << endl;
	}

	cout << "Test Case 4: Deleting Bullets. . ." << endl;
	bullets.clear();
	if (bullets.empty())
	{
		cout << "Successfully deleted bullet in the vector!" << endl << endl;
	}
	else
	{
		cout << "Error: Was unsuccessful to delete bullet in the vector." << endl << endl;
	}

	cout << "Test Case 5: Setting Up The Game. . ." << endl;
	sf::RenderWindow window(sf::VideoMode(1600, 900), "Test");
	ship TheShip(sf::Color::White, 4, window);
	SetUpGame(TheShip, window);
	if (Score == 0 && LevelNumber == 1 && Dead == false && !bigAsteroids.empty())
	{
		cout << "Successfully set up the game!" << endl << endl;
	}
	else
	{
		cout << "Error: Was unsuccessful to set up the game." << endl << endl;
	}

	cout << "==============================" << endl;
}



void Game::SetUpGame(ship TheShip, const sf::RenderWindow &window)
{
	float x = TheShip.getPoint(0).x + TheShip.getPoint(1).x + TheShip.getPoint(2).x;
	x = x / 3;
	float y = TheShip.getPoint(0).y + TheShip.getPoint(1).y + TheShip.getPoint(2).y;
	y = y / 3;

	Score = 0;
	LevelNumber = 1;
	Dead = false;
	bigAsteroids.clear();
	mediumAsteroids.clear();
	smallAsteroids.clear();
	bullets.clear();

	bigAsteroids.push_back(Asteroid(64.f, 15, sf::Vector2f(1400.0, rand() % 900), randomVelocity(), randomVelocity()));
	bigAsteroids.push_back(Asteroid(64.f, 15, sf::Vector2f(200.0, rand() % 900), randomVelocity(), randomVelocity()));

	for (int n = 0; n<1; n++)
	{

		TheShip.setOrigin(x, y);
		TheShip.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	}
}
