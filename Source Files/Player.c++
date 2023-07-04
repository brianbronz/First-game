#include "../Header/Player.h"
#include "../Entities/Entity.c++"
#include "AnimationComponent.c++"
//Initializer functions
void Player::initVariables()
{

}

void Player::initComponents()
{

}

//Constructors / Destructors
Player::Player(float x, float y, Texture& textureSheet)
{
	this->initVariables();
	this->setPosition(x, y);
	this->createMovementComponent(300.f, 15.f, 5.f);
	this->createAnimationComponent(textureSheet);
	this->animationComponent->addAnimation("IDLE_LEFT", 100.f, 0, 0, 13, 0, 192, 192);
	this->animationComponent->addAnimation("WALK_LEFT", 100.f, 0, 1, 11, 1, 192, 192);
}	
//nome file, tempo, numero della colonna da partire, numero della riga, elementi della riga, frames_y, dimensione   
//14 number of image in the row and the following number is for the column (13 because we start from 0)
//width = the width of the file IDLE_LEFT / number of image in the row
//height = the height of the file IDLE_LEFT / number of image in the column

Player::~Player()
{

}

//Functions
void Player::update(const float& dt){
	this->movementComponent->update(dt);

	if(this->movementComponent->getState(IDLE)){
		this->animationComponent->play("IDLE_LEFT", dt): //name file, dt
	} else if(this->movementComponent->getState(MOVING_LEFT)){
		this->animationComponent->play("WALK_LEFT", dt); //name file, dt
	}
}