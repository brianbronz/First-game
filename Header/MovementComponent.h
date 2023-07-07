#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include "AllReference.h"

enum movement_states {IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN};

class MovementComponent{
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
		float& getMaxVelocity();
		Vector2f& getVelocity();

		//Functions
		bool getState(short unsigned state);
		void move( float x,  float y,  float & dt);
		void update( float & dt);
};

#endif