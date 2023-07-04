#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <vector>
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
using namespace std;
using namespace sf;

enum movement_states {IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN};

class MovementComponent
{
private:
	Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;

	Vector2f velocity;

	//Initializer functions

public:
	MovementComponent(Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	//Accessors
	const Vector2f& getVelocity() const;

	//Functions
	bool getState(short unsigned state);
	void move(const float x, const float y, const float & dt);
	void update(const float & dt);
};

#endif