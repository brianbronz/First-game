#include "../Header/Player.h"
#include "../Entities/Entity.c++"
#include "../Animation code/AnimationComponent.c++"
#include "../Weapons/Sword.c++"
//Initializer functions
void Player::initVariables(){
	this->attacking = false;
}

void Player::initComponents(){

}

void Player::initAnimation(){
	//nome file, tempo, numero della colonna da partire, numero della riga, elementi della riga, frames_y, dimensione   
	//14 number of image in the row and the following number is for the column (13 because we start from 0)
	//width = the width of the file IDLE_LEFT / number of image in the row
	//height = the height of the file IDLE_LEFT / number of image in the column
	this->animationComponent->addAnimation("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 11.f, 4, 1, 7, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 8, 1, 11, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_UP", 11.f, 12, 1, 15, 1, 64, 64);
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 64, 64);
}

//ructors / Destructors
Player::Player(float x, float y, Texture& textureSheet){
	this->initVariables();
	this->createHitboxComponent(this->sprite, 12.f, 10.f, 40.f, 54.f);
	this->createMovementComponent(200.f, 1600.f, 1000.f);
	this->createAnimationComponent(textureSheet);
	this->createAttributeComponent(1);
	this->createSkillComponent();
	this->setPosition(x, y);
	this->initAnimation();
}	

Player::~Player(){
}

AttributeComponent * Player::getAttributeComponent(){
	return this->attributeComponent;
}

//Functions
void Player::loseHP(int hp){
	this->attributeComponent->loseHP(hp);
}

void Player::gainHP(int hp){
	this->attributeComponent->gainHP(hp);
}

void Player::loseEXP(int exp){
	this->attributeComponent->exp -= exp;

	if (this->attributeComponent->exp < 0)
		this->attributeComponent->exp = 0;
}

void Player::gainEXP(int exp)
{
	this->attributeComponent->gainExp(exp);
}

void Player::updateAttack(){
	//event to attack
	if(Mouse::isButtonPressed(Mouse::Left)){
		//this->attacking = true;
	}
}

void Player::updateAnimation(float& dt){
	/* if(this->attacking){
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
	} */
	if (this->movementComponent->getState(IDLE)){
		this->animationComponent->play("IDLE", dt);
	} else if (this->movementComponent->getState(MOVING_LEFT)){
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	} else if (this->movementComponent->getState(MOVING_RIGHT)) {
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	} else if (this->movementComponent->getState(MOVING_UP)){
		this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	} else if (this->movementComponent->getState(MOVING_DOWN)){
		this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
}

void Player::update(float& dt, Vector2f& mouse_pos_view){
	this->movementComponent->update(dt);
	this->updateAttack();
	this->updateAnimation(dt);
	this->hitboxComponent->update();
	this->sword.update(mouse_pos_view, this->getCenter());
}

void Player::render(RenderTarget & target, Shader* shader, Vector2f lightPosition, bool show_hitbox){
	if (shader){
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", lightPosition);
		target.draw(this->sprite, shader);
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", lightPosition);
		this->sword.render(target, shader);
	} else { 
		target.draw(this->sprite);
		this->sword.render(target, shader);
	}
	if(show_hitbox){
		this->hitboxComponent->render(target);
	}
}