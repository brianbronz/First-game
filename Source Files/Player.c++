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
	this->animationComponent->addAnimation("IDLE_LEFT", 100.f, 0, 0, 13, 1, 192, 192);//IDLE_LEFT il nome files
}	//14 number of image in the row and the following number is for the column (13 because we start from 0)
//width = the width of the file IDLE_LEFT / number of image in the row
//height = the height of the file IDLE_LEFT / number of image in the column

Player::~Player()
{

}

//Functions
void Player::update(const float& dt){
	this->movementComponent->update(dt);	
	this->animationComponent->play("IDLE_LEFT", dt); //name file, dt
}