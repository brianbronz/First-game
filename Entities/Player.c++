#include "../Header/Player.h"
#include "../Entities/Entity.c++"
#include "../Animation code/AnimationComponent.c++"
//Initializer functions
void Player::initVariables(){
	this->attacking = false;
}

void Player::initComponents(){

}

//ructors / Destructors
Player::Player(float x, float y, Texture& textureSheet){
	this->initVariables();
	this->setPosition(x, y);
	this->createHitboxComponent(this->sprite, 86.f, 74.f, 86.f, 111.f);
	this->createMovementComponent(300.f, 15.f, 5.f);
	this->createAnimationComponent(textureSheet);
	this->animationComponent->addAnimation("IDLE", 100.f, 0, 0, 13, 0, 192, 192);
	this->animationComponent->addAnimation("WALK", 100.f, 0, 1, 11, 1, 192, 192);
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 13, 2, 192*2, 192);
}	
//nome file, tempo, numero della colonna da partire, numero della riga, elementi della riga, frames_y, dimensione   
//14 number of image in the row and the following number is for the column (13 because we start from 0)
//width = the width of the file IDLE_LEFT / number of image in the row
//height = the height of the file IDLE_LEFT / number of image in the column

Player::~Player()
{

}

//Functions
void Player::updateAttack(){
	//event to attack
	if(Mouse::isButtonPressed(Mouse::Left)){
		this->attacking = true;
	}
}

void Player::updateAnimation( float& dt){
	if(this->attacking){
		//Set origin depending on direction
		(this->sprite.getScale().x > 0.f)?
			this->sprite.setOrigin(96.f, 0.f):
			this->sprite.setOrigin(258.f + 96.f, 0.f);
		//Animate and check for the end
		if(this->animationComponent->play("ATTACK", dt, true)){
			this->attacking = false;
			(this->sprite.getScale().x > 0.f)?
				this->sprite.setOrigin(0.f, 0.f):
				this->sprite.setOrigin(258.f, 0.f);
		}
	}
	if(this->movementComponent->getState(IDLE)){
		this->animationComponent->play("IDLE", dt); //name file, dt
	} else if(this->movementComponent->getState(MOVING_LEFT)){
		if(this->sprite.getScale().x < 0.f){
				this->sprite.setOrigin(0.f, 0.f);
				this->sprite.setScale(1.f, 1.f);
		}
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity()); //name file, dt
	} else if(this->movementComponent->getState(MOVING_RIGHT)){
		if(this->sprite.getScale().x > 0.f){
				this->sprite.setOrigin(258.f, 0.f);
				this->sprite.setScale(-1.f, 1.f);
		}
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity()); //name file, dt
	} else if(this->movementComponent->getState(MOVING_DOWN)){
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity()); //name file, dt
	} else if(this->movementComponent->getState(MOVING_UP)){
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity()); //name file, dt
	}

}

void Player::update( float& dt){
	this->movementComponent->update(dt);
	this->updateAttack();
	this->updateAnimation(dt);
	this->hitboxComponent->update();
}