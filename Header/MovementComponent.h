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
#include "../Source Files/SFML-2.6.0/include/SFML/Audio.hpp"
#include "../Source Files/SFML-2.6.0/include/SFML/Graphics.hpp"
#include "../Source Files/SFML-2.6.0/include/SFML/System.hpp"
#include "../Source Files/SFML-2.6.0/include/SFML/Window.hpp"
#include "../Source Files/SFML-2.6.0/include/SFML/Network.hpp"
using namespace std;
using namespace sf;

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
	MovementComponent(Sprite& sprite, 
		float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	//Accessors
	const Vector2f& getVelocity() const;

	//Functions
	void move(const float x, const float y, const float& dt);
	void update(const float& dt);
};

#endif