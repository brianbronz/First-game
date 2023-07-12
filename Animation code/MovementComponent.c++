#include "../Header/MovementComponent.h"

MovementComponent::MovementComponent(Sprite& sprite, float maxVelocity, float acceleration, float deceleration)
: sprite(sprite){
	this->maxVelocity = maxVelocity;
	this->acceleration = acceleration;
	this->deceleration = deceleration;
}

MovementComponent::~MovementComponent(){

}

float & MovementComponent::getMaxVelocity(){
	return this->maxVelocity;
}

Vector2f & MovementComponent::getVelocity(){
	return this->velocity;
}

//Functions
bool MovementComponent::getState(short unsigned state){
	switch (state){
	case IDLE:
		if (this->velocity.x == 0.f && this->velocity.y == 0.f){return true;}
		break;
	case MOVING:
		if (this->velocity.x != 0.f || this->velocity.y != 0.f){return true;}
		break;
	case MOVING_DOWN:
		if (this->velocity.y > 0.f){return true;}
		break;
	
	case MOVING_LEFT:
		if (this->velocity.x < 0.f){return true;}
		break;
	
	case MOVING_RIGHT:
		if (this->velocity.x > 0.f){return true;}
		break;
	
	case MOVING_UP:
		if (this->velocity.y < 0.f){return true;}
		break;
	}
	return false;
}

void MovementComponent::stopVelocity(){
	/* Resets the velocity to 0.*/
	this->velocity.x = 0.f;
	this->velocity.y = 0.f;
}

void MovementComponent::stopVelocityX(){
	/* Resets the velocity x to 0.*/
	this->velocity.x = 0.f;
}

void MovementComponent::stopVelocityY(){
	/* Resets the velocity y to 0.*/
	this->velocity.y = 0.f;
}

void MovementComponent::move(float dir_x, float dir_y, float & dt){
	/* Accelerating a sprite until it reaches the max velocity. */
	this->velocity.x += this->acceleration * dir_x * dt;
	this->velocity.y += this->acceleration * dir_y * dt;	
}

void MovementComponent::update(float & dt){
	/*
	Decelerates the sprite and controls the maximum velocity.
	Moves the sprite.
	*/
	if (this->velocity.x > 0.f){//Check for positive x
		//Max velocity check
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;

		//Deceleration
		this->velocity.x -= deceleration * dt;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
	} else if(this->velocity.x < 0.f){//Check for negative x
		//Max velocity check
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;

		//Deceleration
		this->velocity.x += deceleration * dt;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}

	if (this->velocity.y > 0.f){//Check for positive y
		//Max velocity check
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;

		//Deceleration
		this->velocity.y -= deceleration * dt;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;
	} else if (this->velocity.y < 0.f){//Check for negative y
		//Max velocity check
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;

		//Deceleration
		this->velocity.y += deceleration * dt;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}

	//Final move
	this->sprite.move(this->velocity * dt); //Uses velocity
}