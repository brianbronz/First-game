#include "../Header/Player.h"
#include "../Entities/Entity.c++"
//Initializer functions
void Player::initVariables()
{

}

void Player::initComponents()
{
	this->createMovementComponent(300.f, 15.f, 5.f);
}

//Constructors / Destructors
Player::Player(float x, float y, Texture& texture)
{
	this->initVariables();
	this->initComponents();

	this->setTexture(texture);
	this->setPosition(x, y);
}

Player::~Player()
{

}