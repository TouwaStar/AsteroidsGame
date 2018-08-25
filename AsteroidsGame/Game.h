#include "stdafx.h"
#include "Asteroid.h"
#include "Ship.h"
#include "Bullet.h"
class Game {
private:
	bool checkCollision(const GameObject& object) ; // Checks collision between an object and an asteroid
	int asteroidCollided; // Number of asteroid to be destroyed if collided with a bullet
	float lastTime, timeNow, frameDelta; // Used to determine the time between last update and current one
	void loadLevel(); // Loads the level
public:
	Game(); // Initializes startup variables and srand(), calls LoadLevel()
	void start(int width, int height) const; // Prepares the game for loading, sets up light, background colour etc.
	void update(); // Heart of the game, called in a loop
	Ship player; // Player ship
	std::vector<Asteroid> asteroids; // Vector of currently on screen asteroids
	std::vector<Bullet> bullets; // Vector of currently on screen bullets
};