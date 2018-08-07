#include "stdafx.h"
#include "Asteroid.h"
#include "Ship.h"
#include "Bullet.h"





class Game {
private:
	bool CheckPlayerCollision(); // Checks collision between the player and asteroids
	bool CheckBulletCollision(Bullet bullet,int &numOfAsteroid); // Checks the collision between the bullet and the asteroid, numOfAsteroid is the asteroid which should be destroyed
	int asteroidCollided; // Number of asteroid to be destroyed if collided with a bullet
	float lastTime, timeNow, frameDelta; // Used to determine the time between last update and current one
	void LoadLevel(); // Loads the level
public:
	Game(); // Initializes startup variables and srand(), calls LoadLevel()
	void Start(int width, int height); // Prepares the game for loading, sets up light, background colour etc.
	void Update(); // Heart of the game, called in a loop
	Ship player; // Player ship
	std::vector<Asteroid> asteroids; // Vector of currently on screen asteroids
	std::vector<Bullet> bullets; // Vector of currently on screen bullets
};