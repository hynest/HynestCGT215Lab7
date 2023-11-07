#include <iostream>

#include <SFML/Graphics.hpp>

#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

int main()
{
	// Create our window and world with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));

	// Create the ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(400, 250));
	ball.setRadius(20);
	world.AddPhysicsBody(ball);
	ball.applyImpulse(Vector2f(0.5,0.5));
	
	// Create the floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);
	int thudCount(0);
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount + 1 << endl;
		thudCount++;
		};

	// Create the Ceiling
	PhysicsRectangle Ceiling;
	Ceiling.setSize(Vector2f(800, 20));
	Ceiling.setCenter(Vector2f(400, 10));
	Ceiling.setStatic(true);
	world.AddPhysicsBody(Ceiling);
	Ceiling.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount + 1 << endl;
		thudCount++;
		};

	// Create Left Wall
	PhysicsRectangle LWall;
	LWall.setSize(Vector2f(20, 600));
	LWall.setCenter(Vector2f(10, 300));
	LWall.setStatic(true);
	world.AddPhysicsBody(LWall);
	LWall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount + 1 << endl;
		thudCount++;
		};
	
	// Create Right Wall
	PhysicsRectangle RWall;
	RWall.setSize(Vector2f(20, 600));
	RWall.setCenter(Vector2f(790, 300));
	RWall.setStatic(true);
	world.AddPhysicsBody(RWall);
	RWall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount+1 << endl;
		thudCount++;
		};

	// Create the Obstacle
	PhysicsRectangle Block;
	Block.setSize(Vector2f(200, 40));
	Block.setCenter(Vector2f(400, 400));
	Block.setStatic(true);
	world.AddPhysicsBody(Block);
	int bangCount(0);
	Block.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
		cout << "Bang " << bangCount+1 << endl;
		bangCount++;
		};

	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (true) {
		// calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
			if (bangCount == 3) {
				exit(0);
			}
		}
		window.clear(Color(0, 0, 0));
		window.draw(ball);
		window.draw(floor);
		window.draw(Ceiling);
		window.draw(LWall);
		window.draw(RWall);
		window.draw(Block);
		window.display();
	}
}